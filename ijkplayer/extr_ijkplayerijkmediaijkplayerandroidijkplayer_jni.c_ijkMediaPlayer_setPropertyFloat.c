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
typedef  int /*<<< orphan*/  jfloat ;
typedef  int /*<<< orphan*/  JNIEnv ;
typedef  int /*<<< orphan*/  IjkMediaPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  JNI_CHECK_GOTO (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LABEL_RETURN ; 
 int /*<<< orphan*/  ijkmp_dec_ref_p (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ijkmp_set_property_float (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * jni_get_media_player (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ijkMediaPlayer_setPropertyFloat(JNIEnv *env, jobject thiz, jint id, jfloat value)
{
    IjkMediaPlayer *mp = jni_get_media_player(env, thiz);
    JNI_CHECK_GOTO(mp, env, NULL, "mpjni: setPropertyFloat: null mp", LABEL_RETURN);

    ijkmp_set_property_float(mp, id, value);

LABEL_RETURN:
    ijkmp_dec_ref_p(&mp);
    return;
}