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
 scalar_t__ J4AC_tv_danmaku_ijk_media_player_misc_IAndroidIO__open__catchAll (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  J4A_DeleteLocalRef__p (TYPE_1__**,int /*<<< orphan*/ **) ; 
 scalar_t__ J4A_ExceptionCheck__catchAll (TYPE_1__**) ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__**,char const*) ; 

jint J4AC_tv_danmaku_ijk_media_player_misc_IAndroidIO__open__withCString__catchAll(JNIEnv *env, jobject thiz, const char *url_cstr__)
{
    jint ret_value = 0;
    jstring url = NULL;

    url = (*env)->NewStringUTF(env, url_cstr__);
    if (J4A_ExceptionCheck__catchAll(env) || !url)
        goto fail;

    ret_value = J4AC_tv_danmaku_ijk_media_player_misc_IAndroidIO__open__catchAll(env, thiz, url);
    if (J4A_ExceptionCheck__catchAll(env)) {
        ret_value = 0;
        goto fail;
    }

fail:
    J4A_DeleteLocalRef__p(env, &url);
    return ret_value;
}