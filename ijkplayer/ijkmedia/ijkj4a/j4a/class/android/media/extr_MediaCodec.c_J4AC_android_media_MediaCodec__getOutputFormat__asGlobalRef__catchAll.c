#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/ * jobject ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/ * J4AC_android_media_MediaCodec__getOutputFormat__catchAll (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  J4A_DeleteLocalRef__p (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ J4A_ExceptionCheck__catchAll (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * J4A_NewGlobalRef__catchAll (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

jobject J4AC_android_media_MediaCodec__getOutputFormat__asGlobalRef__catchAll(JNIEnv *env, jobject thiz)
{
    jobject ret_object   = NULL;
    jobject local_object = J4AC_android_media_MediaCodec__getOutputFormat__catchAll(env, thiz);
    if (J4A_ExceptionCheck__catchAll(env) || !local_object) {
        ret_object = NULL;
        goto fail;
    }

    ret_object = J4A_NewGlobalRef__catchAll(env, local_object);
    if (!ret_object) {
        ret_object = NULL;
        goto fail;
    }

fail:
    J4A_DeleteLocalRef__p(env, &local_object);
    return ret_object;
}