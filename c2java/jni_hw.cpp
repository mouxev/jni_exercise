#include<jni.h>
#include<stdio.h>

int main(int argc, char** argv) {

    JavaVM *vm;
    JNIEnv *env = NULL;
    JavaVMInitArgs vm_args;
    vm_args.version = JNI_VERSION_1_2;
    vm_args.nOptions = 0;
    vm_args.ignoreUnrecognized = 1;

    // Construct a VM
    jint res = JNI_CreateJavaVM(&vm, (void **)&env, &vm_args);

    // Construct a String
    jstring jstr = env->NewStringUTF("Hello World");

    // First get the class that contains the method you need to call
    jclass clazz = env->FindClass("java/lang/String");

    // Get the method that you want to call
    jmethodID to_lower = env->GetMethodID(clazz, "toLowerCase",
                                      "()Ljava/lang/String;");
    // Call the method on the object
    jobject result = env->CallObjectMethod(jstr, to_lower);
	
	
    // Get a C-style string
    const char* str = env->GetStringUTFChars((jstring) result, NULL);
    printf("%s\n", str);

	jclass syscls = env->FindClass("java/lang/System");
	jfieldID fid = env->GetStaticFieldID(syscls, "in", "Ljava/io/InputStream;");
	jobject in  = env->GetStaticObjectField(syscls, fid);
	jclass iscls = env->FindClass("java/io/InputStream");
	jmethodID mid = env->GetMethodID(iscls, "read", "");
	// 
	env->CallVoidMethod(env, in, mid, "()V" );	
	
    // Clean up
    env->ReleaseStringUTFChars(jstr, str);

    // Shutdown the VM.
    vm->DestroyJavaVM();
}