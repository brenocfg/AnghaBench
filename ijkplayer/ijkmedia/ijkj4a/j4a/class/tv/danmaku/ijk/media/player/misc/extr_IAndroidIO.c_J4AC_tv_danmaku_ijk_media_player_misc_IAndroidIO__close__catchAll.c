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
typedef  int /*<<< orphan*/  jobject ;
typedef  int /*<<< orphan*/  jint ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  J4AC_tv_danmaku_ijk_media_player_misc_IAndroidIO__close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ J4A_ExceptionCheck__catchAll (int /*<<< orphan*/ *) ; 

jint J4AC_tv_danmaku_ijk_media_player_misc_IAndroidIO__close__catchAll(JNIEnv *env, jobject thiz)
{
    jint ret_value = J4AC_tv_danmaku_ijk_media_player_misc_IAndroidIO__close(env, thiz);
    if (J4A_ExceptionCheck__catchAll(env)) {
        return 0;
    }

    return ret_value;
}