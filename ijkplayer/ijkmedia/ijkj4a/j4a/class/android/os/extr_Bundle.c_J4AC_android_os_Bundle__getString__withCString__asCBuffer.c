#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jstring ;
typedef  int /*<<< orphan*/  jobject ;
struct TYPE_8__ {char* (* GetStringUTFChars ) (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  J4AC_android_os_Bundle__getString__withCString (TYPE_1__**,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  J4A_DeleteLocalRef__p (TYPE_1__**,int /*<<< orphan*/ *) ; 
 scalar_t__ J4A_ExceptionCheck__throwAny (TYPE_1__**) ; 
 int /*<<< orphan*/  J4A_ReleaseStringUTFChars__p (TYPE_1__**,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 char* stub1 (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

const char *J4AC_android_os_Bundle__getString__withCString__asCBuffer(JNIEnv *env, jobject thiz, const char *key_cstr__, char *out_buf, int out_len)
{
    const char *ret_value = NULL;
    const char *c_str     = NULL;
    jstring local_string = J4AC_android_os_Bundle__getString__withCString(env, thiz, key_cstr__);
    if (J4A_ExceptionCheck__throwAny(env) || !local_string) {
        goto fail;
    }

    c_str = (*env)->GetStringUTFChars(env, local_string, NULL );
    if (J4A_ExceptionCheck__throwAny(env) || !c_str) {
        goto fail;
    }

    strlcpy(out_buf, c_str, out_len);
    ret_value = out_buf;

fail:
    J4A_ReleaseStringUTFChars__p(env, local_string, &c_str);
    J4A_DeleteLocalRef__p(env, &local_string);
    return ret_value;
}