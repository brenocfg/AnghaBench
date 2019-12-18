#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jstring ;
typedef  int /*<<< orphan*/  jobject ;
typedef  int /*<<< orphan*/  jint ;
struct TYPE_6__ {int /*<<< orphan*/  method_onSelectCodec; int /*<<< orphan*/  id; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* CallStaticObjectMethod ) (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 TYPE_3__ class_J4AC_tv_danmaku_ijk_media_player_IjkMediaPlayer ; 
 int /*<<< orphan*/  stub1 (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

jstring J4AC_tv_danmaku_ijk_media_player_IjkMediaPlayer__onSelectCodec(JNIEnv *env, jobject weakThiz, jstring mimeType, jint profile, jint level)
{
    return (*env)->CallStaticObjectMethod(env, class_J4AC_tv_danmaku_ijk_media_player_IjkMediaPlayer.id, class_J4AC_tv_danmaku_ijk_media_player_IjkMediaPlayer.method_onSelectCodec, weakThiz, mimeType, profile, level);
}