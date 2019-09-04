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
typedef  char const* jstring ;
typedef  int /*<<< orphan*/  jobject ;
typedef  int /*<<< orphan*/  jlong ;
typedef  int /*<<< orphan*/  jint ;
struct TYPE_7__ {char* (* GetStringUTFChars ) (TYPE_1__**,char const*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* ReleaseStringUTFChars ) (TYPE_1__**,char const*,char const*) ;} ;
typedef  TYPE_1__* JNIEnv ;
typedef  char const IjkMediaPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  ALOGV (char*,char const*) ; 
 int /*<<< orphan*/  JNI_CHECK_GOTO (char const*,TYPE_1__**,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LABEL_RETURN ; 
 int /*<<< orphan*/  ijkmp_dec_ref_p (char const**) ; 
 int /*<<< orphan*/  ijkmp_set_frame_at_time (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* jni_get_media_player (TYPE_1__**,int /*<<< orphan*/ ) ; 
 char* stub1 (TYPE_1__**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__**,char const*,char const*) ; 

__attribute__((used)) static void
IjkMediaPlayer_setFrameAtTime(JNIEnv *env, jobject thiz, jstring path, jlong start_time, jlong end_time, jint num, jint definition) {
    IjkMediaPlayer *mp = jni_get_media_player(env, thiz);
    const char *c_path = NULL;
    JNI_CHECK_GOTO(path, env, "java/lang/IllegalArgumentException", "mpjni: setFrameAtTime: null path", LABEL_RETURN);
    JNI_CHECK_GOTO(mp, env, "java/lang/IllegalStateException", "mpjni: setFrameAtTime: null mp", LABEL_RETURN);

    c_path = (*env)->GetStringUTFChars(env, path, NULL );
    JNI_CHECK_GOTO(c_path, env, "java/lang/OutOfMemoryError", "mpjni: setFrameAtTime: path.string oom", LABEL_RETURN);

    ALOGV("setFrameAtTime: path %s", c_path);
    ijkmp_set_frame_at_time(mp, c_path, start_time, end_time, num, definition);
    (*env)->ReleaseStringUTFChars(env, path, c_path);

LABEL_RETURN:
    ijkmp_dec_ref_p(&mp);
    return;
}