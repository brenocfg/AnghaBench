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
typedef  int /*<<< orphan*/  jint ;
struct TYPE_7__ {int /*<<< orphan*/ * (* NewStringUTF ) (TYPE_1__**,char const*) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/ * J4AC_tv_danmaku_ijk_media_player_IjkMediaPlayer__onSelectCodec__catchAll (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  J4A_DeleteLocalRef__p (TYPE_1__**,int /*<<< orphan*/ **) ; 
 scalar_t__ J4A_ExceptionCheck__catchAll (TYPE_1__**) ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__**,char const*) ; 

jstring J4AC_tv_danmaku_ijk_media_player_IjkMediaPlayer__onSelectCodec__withCString__catchAll(JNIEnv *env, jobject weakThiz, const char *mimeType_cstr__, jint profile, jint level)
{
    jstring ret_object = NULL;
    jstring mimeType = NULL;

    mimeType = (*env)->NewStringUTF(env, mimeType_cstr__);
    if (J4A_ExceptionCheck__catchAll(env) || !mimeType)
        goto fail;

    ret_object = J4AC_tv_danmaku_ijk_media_player_IjkMediaPlayer__onSelectCodec__catchAll(env, weakThiz, mimeType, profile, level);
    if (J4A_ExceptionCheck__catchAll(env) || !ret_object) {
        ret_object = NULL;
        goto fail;
    }

fail:
    J4A_DeleteLocalRef__p(env, &mimeType);
    return ret_object;
}