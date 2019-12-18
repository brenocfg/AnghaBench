#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * jstring ;
typedef  int /*<<< orphan*/  jobject ;
typedef  scalar_t__ jint ;
struct TYPE_7__ {int /*<<< orphan*/ * (* NewStringUTF ) (TYPE_1__**,char const*) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 scalar_t__ J4AC_android_media_MediaFormat__getInteger (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  J4A_DeleteLocalRef__p (TYPE_1__**,int /*<<< orphan*/ **) ; 
 scalar_t__ J4A_ExceptionCheck__throwAny (TYPE_1__**) ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__**,char const*) ; 

jint J4AC_android_media_MediaFormat__getInteger__withCString(JNIEnv *env, jobject thiz, const char *name_cstr__)
{
    jint ret_value = 0;
    jstring name = NULL;

    name = (*env)->NewStringUTF(env, name_cstr__);
    if (J4A_ExceptionCheck__throwAny(env) || !name)
        goto fail;

    ret_value = J4AC_android_media_MediaFormat__getInteger(env, thiz, name);
    if (J4A_ExceptionCheck__throwAny(env)) {
        ret_value = 0;
        goto fail;
    }

fail:
    J4A_DeleteLocalRef__p(env, &name);
    return ret_value;
}