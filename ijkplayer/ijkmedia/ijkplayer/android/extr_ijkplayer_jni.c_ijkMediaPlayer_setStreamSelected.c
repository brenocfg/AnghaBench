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
typedef  int /*<<< orphan*/  jboolean ;
typedef  int /*<<< orphan*/  JNIEnv ;
typedef  int /*<<< orphan*/  IjkMediaPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  ALOGE (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JNI_CHECK_GOTO (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LABEL_RETURN ; 
 int /*<<< orphan*/  ijkmp_dec_ref_p (int /*<<< orphan*/ **) ; 
 int ijkmp_set_stream_selected (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * jni_get_media_player (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ijkMediaPlayer_setStreamSelected(JNIEnv *env, jobject thiz, jint stream, jboolean selected)
{
    IjkMediaPlayer *mp = jni_get_media_player(env, thiz);
    int ret = 0;
    JNI_CHECK_GOTO(mp, env, NULL, "mpjni: setStreamSelected: null mp", LABEL_RETURN);

    ret = ijkmp_set_stream_selected(mp, stream, selected);
    if (ret < 0) {
        ALOGE("failed to %s %d", selected ? "select" : "deselect", stream);
        goto LABEL_RETURN;
    }

LABEL_RETURN:
    ijkmp_dec_ref_p(&mp);
    return;
}