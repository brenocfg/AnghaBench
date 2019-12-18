#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int abort_request; scalar_t__ audio_stream; scalar_t__ video_stream; scalar_t__ subtitle_stream; struct TYPE_7__* filename; int /*<<< orphan*/ * handle; scalar_t__ sub_convert_ctx; scalar_t__ img_convert_ctx; int /*<<< orphan*/  play_mutex; int /*<<< orphan*/  accurate_seek_mutex; int /*<<< orphan*/  continue_read_thread; int /*<<< orphan*/  video_accurate_seek_cond; int /*<<< orphan*/  audio_accurate_seek_cond; int /*<<< orphan*/  subpq; int /*<<< orphan*/  sampq; int /*<<< orphan*/  pictq; int /*<<< orphan*/  subtitleq; int /*<<< orphan*/  audioq; int /*<<< orphan*/  videoq; int /*<<< orphan*/  video_refresh_tid; int /*<<< orphan*/  ic; int /*<<< orphan*/  read_tid; } ;
typedef  TYPE_1__ VideoState ;
struct TYPE_9__ {struct TYPE_9__* img_path; scalar_t__ frame_img_codec_ctx; scalar_t__ frame_img_convert_ctx; } ;
struct TYPE_8__ {TYPE_1__* is; TYPE_5__* get_img_info; scalar_t__ soundtouch_enable; } ;
typedef  TYPE_2__ FFPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  SDL_DestroyCond (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_DestroyMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_WaitThread (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_free (TYPE_1__*) ; 
 int /*<<< orphan*/  av_freep (TYPE_5__**) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avcodec_free_context (scalar_t__*) ; 
 int /*<<< orphan*/  avformat_close_input (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frame_queue_destory (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ijk_soundtouch_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  packet_queue_abort (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  packet_queue_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stream_component_close (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  sws_freeContext (scalar_t__) ; 

__attribute__((used)) static void stream_close(FFPlayer *ffp)
{
    VideoState *is = ffp->is;
    /* XXX: use a special url_shutdown call to abort parse cleanly */
    is->abort_request = 1;
    packet_queue_abort(&is->videoq);
    packet_queue_abort(&is->audioq);
    av_log(NULL, AV_LOG_DEBUG, "wait for read_tid\n");
    SDL_WaitThread(is->read_tid, NULL);

    /* close each stream */
    if (is->audio_stream >= 0)
        stream_component_close(ffp, is->audio_stream);
    if (is->video_stream >= 0)
        stream_component_close(ffp, is->video_stream);
    if (is->subtitle_stream >= 0)
        stream_component_close(ffp, is->subtitle_stream);

    avformat_close_input(&is->ic);

    av_log(NULL, AV_LOG_DEBUG, "wait for video_refresh_tid\n");
    SDL_WaitThread(is->video_refresh_tid, NULL);

    packet_queue_destroy(&is->videoq);
    packet_queue_destroy(&is->audioq);
    packet_queue_destroy(&is->subtitleq);

    /* free all pictures */
    frame_queue_destory(&is->pictq);
    frame_queue_destory(&is->sampq);
    frame_queue_destory(&is->subpq);
    SDL_DestroyCond(is->audio_accurate_seek_cond);
    SDL_DestroyCond(is->video_accurate_seek_cond);
    SDL_DestroyCond(is->continue_read_thread);
    SDL_DestroyMutex(is->accurate_seek_mutex);
    SDL_DestroyMutex(is->play_mutex);
#if !CONFIG_AVFILTER
    sws_freeContext(is->img_convert_ctx);
#endif
#ifdef FFP_MERGE
    sws_freeContext(is->sub_convert_ctx);
#endif

#if defined(__ANDROID__)
    if (ffp->soundtouch_enable && is->handle != NULL) {
        ijk_soundtouch_destroy(is->handle);
    }
#endif
    if (ffp->get_img_info) {
        if (ffp->get_img_info->frame_img_convert_ctx) {
            sws_freeContext(ffp->get_img_info->frame_img_convert_ctx);
        }
        if (ffp->get_img_info->frame_img_codec_ctx) {
            avcodec_free_context(&ffp->get_img_info->frame_img_codec_ctx);
        }
        av_freep(&ffp->get_img_info->img_path);
        av_freep(&ffp->get_img_info);
    }
    av_free(is->filename);
    av_free(is);
    ffp->is = NULL;
}