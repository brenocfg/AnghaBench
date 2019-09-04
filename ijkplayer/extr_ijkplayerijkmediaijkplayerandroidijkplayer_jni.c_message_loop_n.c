#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * jstring ;
typedef  int /*<<< orphan*/  jobject ;
struct TYPE_13__ {int what; int /*<<< orphan*/  arg1; int /*<<< orphan*/  arg2; scalar_t__ obj; } ;
struct TYPE_12__ {int /*<<< orphan*/ * (* NewStringUTF ) (TYPE_1__**,char*) ;} ;
typedef  TYPE_1__* JNIEnv ;
typedef  int /*<<< orphan*/  IjkMediaPlayer ;
typedef  TYPE_2__ AVMessage ;

/* Variables and functions */
 int /*<<< orphan*/  ALOGE (char*,int) ; 
#define  FFP_MSG_ACCURATE_SEEK_COMPLETE 153 
#define  FFP_MSG_AUDIO_DECODED_START 152 
#define  FFP_MSG_AUDIO_RENDERING_START 151 
#define  FFP_MSG_AUDIO_SEEK_RENDERING_START 150 
#define  FFP_MSG_BUFFERING_BYTES_UPDATE 149 
#define  FFP_MSG_BUFFERING_END 148 
#define  FFP_MSG_BUFFERING_START 147 
#define  FFP_MSG_BUFFERING_TIME_UPDATE 146 
#define  FFP_MSG_BUFFERING_UPDATE 145 
#define  FFP_MSG_COMPLETED 144 
#define  FFP_MSG_COMPONENT_OPEN 143 
#define  FFP_MSG_ERROR 142 
#define  FFP_MSG_FIND_STREAM_INFO 141 
#define  FFP_MSG_FLUSH 140 
#define  FFP_MSG_GET_IMG_STATE 139 
#define  FFP_MSG_OPEN_INPUT 138 
#define  FFP_MSG_PLAYBACK_STATE_CHANGED 137 
#define  FFP_MSG_PREPARED 136 
#define  FFP_MSG_SAR_CHANGED 135 
#define  FFP_MSG_SEEK_COMPLETE 134 
#define  FFP_MSG_TIMED_TEXT 133 
#define  FFP_MSG_VIDEO_DECODED_START 132 
#define  FFP_MSG_VIDEO_RENDERING_START 131 
#define  FFP_MSG_VIDEO_ROTATION_CHANGED 130 
#define  FFP_MSG_VIDEO_SEEK_RENDERING_START 129 
#define  FFP_MSG_VIDEO_SIZE_CHANGED 128 
 int /*<<< orphan*/  J4A_DeleteLocalRef__p (TYPE_1__**,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  JNI_CHECK_GOTO (int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LABEL_RETURN ; 
 int /*<<< orphan*/  MEDIA_BUFFERING_UPDATE ; 
 int /*<<< orphan*/  MEDIA_ERROR ; 
 int /*<<< orphan*/  MEDIA_ERROR_IJK_PLAYER ; 
 int /*<<< orphan*/  MEDIA_GET_IMG_STATE ; 
 int /*<<< orphan*/  MEDIA_INFO ; 
 int /*<<< orphan*/  MEDIA_INFO_AUDIO_DECODED_START ; 
 int /*<<< orphan*/  MEDIA_INFO_AUDIO_RENDERING_START ; 
 int /*<<< orphan*/  MEDIA_INFO_AUDIO_SEEK_RENDERING_START ; 
 int /*<<< orphan*/  MEDIA_INFO_BUFFERING_END ; 
 int /*<<< orphan*/  MEDIA_INFO_BUFFERING_START ; 
 int /*<<< orphan*/  MEDIA_INFO_COMPONENT_OPEN ; 
 int /*<<< orphan*/  MEDIA_INFO_FIND_STREAM_INFO ; 
 int /*<<< orphan*/  MEDIA_INFO_MEDIA_ACCURATE_SEEK_COMPLETE ; 
 int /*<<< orphan*/  MEDIA_INFO_OPEN_INPUT ; 
 int /*<<< orphan*/  MEDIA_INFO_VIDEO_DECODED_START ; 
 int /*<<< orphan*/  MEDIA_INFO_VIDEO_RENDERING_START ; 
 int /*<<< orphan*/  MEDIA_INFO_VIDEO_ROTATION_CHANGED ; 
 int /*<<< orphan*/  MEDIA_INFO_VIDEO_SEEK_RENDERING_START ; 
 int /*<<< orphan*/  MEDIA_NOP ; 
 int /*<<< orphan*/  MEDIA_PLAYBACK_COMPLETE ; 
 int /*<<< orphan*/  MEDIA_PREPARED ; 
 int /*<<< orphan*/  MEDIA_SEEK_COMPLETE ; 
 int /*<<< orphan*/  MEDIA_SET_VIDEO_SAR ; 
 int /*<<< orphan*/  MEDIA_SET_VIDEO_SIZE ; 
 int /*<<< orphan*/  MEDIA_TIMED_TEXT ; 
 int /*<<< orphan*/  MPTRACE (char*,...) ; 
 int /*<<< orphan*/  assert (int) ; 
 int ijkmp_get_msg (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  ijkmp_get_weak_thiz (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_free_res (TYPE_2__*) ; 
 int /*<<< orphan*/  post_event (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  post_event2 (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__**,char*) ; 
 int /*<<< orphan*/ * stub2 (TYPE_1__**,char*) ; 

__attribute__((used)) static void message_loop_n(JNIEnv *env, IjkMediaPlayer *mp)
{
    jobject weak_thiz = (jobject) ijkmp_get_weak_thiz(mp);
    JNI_CHECK_GOTO(weak_thiz, env, NULL, "mpjni: message_loop_n: null weak_thiz", LABEL_RETURN);

    while (1) {
        AVMessage msg;

        int retval = ijkmp_get_msg(mp, &msg, 1);
        if (retval < 0)
            break;

        // block-get should never return 0
        assert(retval > 0);

        switch (msg.what) {
        case FFP_MSG_FLUSH:
            MPTRACE("FFP_MSG_FLUSH:\n");
            post_event(env, weak_thiz, MEDIA_NOP, 0, 0);
            break;
        case FFP_MSG_ERROR:
            MPTRACE("FFP_MSG_ERROR: %d\n", msg.arg1);
            post_event(env, weak_thiz, MEDIA_ERROR, MEDIA_ERROR_IJK_PLAYER, msg.arg1);
            break;
        case FFP_MSG_PREPARED:
            MPTRACE("FFP_MSG_PREPARED:\n");
            post_event(env, weak_thiz, MEDIA_PREPARED, 0, 0);
            break;
        case FFP_MSG_COMPLETED:
            MPTRACE("FFP_MSG_COMPLETED:\n");
            post_event(env, weak_thiz, MEDIA_PLAYBACK_COMPLETE, 0, 0);
            break;
        case FFP_MSG_VIDEO_SIZE_CHANGED:
            MPTRACE("FFP_MSG_VIDEO_SIZE_CHANGED: %d, %d\n", msg.arg1, msg.arg2);
            post_event(env, weak_thiz, MEDIA_SET_VIDEO_SIZE, msg.arg1, msg.arg2);
            break;
        case FFP_MSG_SAR_CHANGED:
            MPTRACE("FFP_MSG_SAR_CHANGED: %d, %d\n", msg.arg1, msg.arg2);
            post_event(env, weak_thiz, MEDIA_SET_VIDEO_SAR, msg.arg1, msg.arg2);
            break;
        case FFP_MSG_VIDEO_RENDERING_START:
            MPTRACE("FFP_MSG_VIDEO_RENDERING_START:\n");
            post_event(env, weak_thiz, MEDIA_INFO, MEDIA_INFO_VIDEO_RENDERING_START, 0);
            break;
        case FFP_MSG_AUDIO_RENDERING_START:
            MPTRACE("FFP_MSG_AUDIO_RENDERING_START:\n");
            post_event(env, weak_thiz, MEDIA_INFO, MEDIA_INFO_AUDIO_RENDERING_START, 0);
            break;
        case FFP_MSG_VIDEO_ROTATION_CHANGED:
            MPTRACE("FFP_MSG_VIDEO_ROTATION_CHANGED: %d\n", msg.arg1);
            post_event(env, weak_thiz, MEDIA_INFO, MEDIA_INFO_VIDEO_ROTATION_CHANGED, msg.arg1);
            break;
        case FFP_MSG_AUDIO_DECODED_START:
            MPTRACE("FFP_MSG_AUDIO_DECODED_START:\n");
            post_event(env, weak_thiz, MEDIA_INFO, MEDIA_INFO_AUDIO_DECODED_START, 0);
            break;
        case FFP_MSG_VIDEO_DECODED_START:
            MPTRACE("FFP_MSG_VIDEO_DECODED_START:\n");
            post_event(env, weak_thiz, MEDIA_INFO, MEDIA_INFO_VIDEO_DECODED_START, 0);
            break;
        case FFP_MSG_OPEN_INPUT:
            MPTRACE("FFP_MSG_OPEN_INPUT:\n");
            post_event(env, weak_thiz, MEDIA_INFO, MEDIA_INFO_OPEN_INPUT, 0);
            break;
        case FFP_MSG_FIND_STREAM_INFO:
            MPTRACE("FFP_MSG_FIND_STREAM_INFO:\n");
            post_event(env, weak_thiz, MEDIA_INFO, MEDIA_INFO_FIND_STREAM_INFO, 0);
            break;
        case FFP_MSG_COMPONENT_OPEN:
            MPTRACE("FFP_MSG_COMPONENT_OPEN:\n");
            post_event(env, weak_thiz, MEDIA_INFO, MEDIA_INFO_COMPONENT_OPEN, 0);
            break;
        case FFP_MSG_BUFFERING_START:
            MPTRACE("FFP_MSG_BUFFERING_START:\n");
            post_event(env, weak_thiz, MEDIA_INFO, MEDIA_INFO_BUFFERING_START, msg.arg1);
            break;
        case FFP_MSG_BUFFERING_END:
            MPTRACE("FFP_MSG_BUFFERING_END:\n");
            post_event(env, weak_thiz, MEDIA_INFO, MEDIA_INFO_BUFFERING_END, msg.arg1);
            break;
        case FFP_MSG_BUFFERING_UPDATE:
            // MPTRACE("FFP_MSG_BUFFERING_UPDATE: %d, %d", msg.arg1, msg.arg2);
            post_event(env, weak_thiz, MEDIA_BUFFERING_UPDATE, msg.arg1, msg.arg2);
            break;
        case FFP_MSG_BUFFERING_BYTES_UPDATE:
            break;
        case FFP_MSG_BUFFERING_TIME_UPDATE:
            break;
        case FFP_MSG_SEEK_COMPLETE:
            MPTRACE("FFP_MSG_SEEK_COMPLETE:\n");
            post_event(env, weak_thiz, MEDIA_SEEK_COMPLETE, 0, 0);
            break;
        case FFP_MSG_ACCURATE_SEEK_COMPLETE:
            MPTRACE("FFP_MSG_ACCURATE_SEEK_COMPLETE:\n");
            post_event(env, weak_thiz, MEDIA_INFO, MEDIA_INFO_MEDIA_ACCURATE_SEEK_COMPLETE, msg.arg1);
            break;
        case FFP_MSG_PLAYBACK_STATE_CHANGED:
            break;
        case FFP_MSG_TIMED_TEXT:
            if (msg.obj) {
                jstring text = (*env)->NewStringUTF(env, (char *)msg.obj);
                post_event2(env, weak_thiz, MEDIA_TIMED_TEXT, 0, 0, text);
                J4A_DeleteLocalRef__p(env, &text);
            }
            else {
                post_event2(env, weak_thiz, MEDIA_TIMED_TEXT, 0, 0, NULL);
            }
            break;
        case FFP_MSG_GET_IMG_STATE:
            if (msg.obj) {
                jstring file_name = (*env)->NewStringUTF(env, (char *)msg.obj);
                post_event2(env, weak_thiz, MEDIA_GET_IMG_STATE, msg.arg1, msg.arg2, file_name);
                J4A_DeleteLocalRef__p(env, &file_name);
            }
            else {
                post_event2(env, weak_thiz, MEDIA_GET_IMG_STATE, msg.arg1, msg.arg2, NULL);
            }
            break;
        case FFP_MSG_VIDEO_SEEK_RENDERING_START:
            MPTRACE("FFP_MSG_VIDEO_SEEK_RENDERING_START:\n");
            post_event(env, weak_thiz, MEDIA_INFO, MEDIA_INFO_VIDEO_SEEK_RENDERING_START, msg.arg1);
            break;
        case FFP_MSG_AUDIO_SEEK_RENDERING_START:
            MPTRACE("FFP_MSG_AUDIO_SEEK_RENDERING_START:\n");
            post_event(env, weak_thiz, MEDIA_INFO, MEDIA_INFO_AUDIO_SEEK_RENDERING_START, msg.arg1);
            break;
        default:
            ALOGE("unknown FFP_MSG_xxx(%d)\n", msg.what);
            break;
        }
        msg_free_res(&msg);
    }

LABEL_RETURN:
    ;
}