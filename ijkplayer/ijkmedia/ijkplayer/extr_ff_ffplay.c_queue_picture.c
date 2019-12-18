#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_16__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_23__ {int first_frame_decoded; int /*<<< orphan*/  first_frame_decoded_time; } ;
struct TYPE_21__ {scalar_t__ abort_request; } ;
struct TYPE_24__ {int video_accurate_seek_req; scalar_t__ seek_pos; double accurate_seek_vframe_pts; scalar_t__ accurate_seek_start_time; scalar_t__ audio_stream; scalar_t__ accurate_seek_aframe_pts; TYPE_3__ viddec; int /*<<< orphan*/  pictq; TYPE_1__ videoq; int /*<<< orphan*/  accurate_seek_mutex; int /*<<< orphan*/  video_accurate_seek_cond; int /*<<< orphan*/  abort_request; scalar_t__ audio_accurate_seek_req; int /*<<< orphan*/  audio_accurate_seek_cond; int /*<<< orphan*/  drop_vframe_count; int /*<<< orphan*/  seek_req; } ;
typedef  TYPE_4__ VideoState ;
struct TYPE_22__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_27__ {scalar_t__ width; scalar_t__ height; scalar_t__ format; TYPE_2__ sample_aspect_ratio; int /*<<< orphan*/  linesize; scalar_t__ data; int /*<<< orphan*/  pict_type; } ;
struct TYPE_26__ {scalar_t__ accurate_seek_timeout; scalar_t__ enable_accurate_seek; TYPE_4__* is; } ;
struct TYPE_25__ {scalar_t__ width; scalar_t__ height; scalar_t__ format; double pts; double duration; int serial; int /*<<< orphan*/  frame; TYPE_2__ sar; TYPE_16__* bmp; scalar_t__ pos; scalar_t__ allocated; scalar_t__ uploaded; } ;
struct TYPE_20__ {int /*<<< orphan*/  sar_den; int /*<<< orphan*/  sar_num; } ;
typedef  TYPE_5__ Frame ;
typedef  TYPE_6__ FFPlayer ;
typedef  TYPE_7__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  ALOGD (char*) ; 
 int /*<<< orphan*/  AV_LOG_FATAL ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  FFP_MSG_ACCURATE_SEEK_COMPLETE ; 
 int /*<<< orphan*/  FFP_MSG_VIDEO_DECODED_START ; 
 int /*<<< orphan*/  FFP_MSG_VIDEO_SIZE_CHANGED ; 
 scalar_t__ MAX_DEVIATION ; 
 int /*<<< orphan*/  SDL_CondSignal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_CondWaitTimeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SDL_GetTickHR () ; 
 int /*<<< orphan*/  SDL_LockMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_UnlockMutex (int /*<<< orphan*/ ) ; 
 scalar_t__ SDL_VoutFillFrameYUVOverlay (TYPE_16__*,TYPE_7__*) ; 
 int /*<<< orphan*/  SDL_VoutLockYUVOverlay (TYPE_16__*) ; 
 int /*<<< orphan*/  SDL_VoutUnlockYUVOverlay (TYPE_16__*) ; 
 int /*<<< orphan*/  alloc_picture (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  av_frame_move_ref (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int av_get_picture_type_char (int /*<<< orphan*/ ) ; 
 int av_gettime_relative () ; 
 int /*<<< orphan*/  av_image_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_usleep (int) ; 
 int /*<<< orphan*/  data ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  ffp_notify_msg1 (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffp_notify_msg2 (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ffp_notify_msg3 (TYPE_6__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 TYPE_5__* frame_queue_peek_writable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frame_queue_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isnan (double) ; 
 int /*<<< orphan*/  linesize ; 
 scalar_t__ llabs (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,int,double) ; 

__attribute__((used)) static int queue_picture(FFPlayer *ffp, AVFrame *src_frame, double pts, double duration, int64_t pos, int serial)
{
    VideoState *is = ffp->is;
    Frame *vp;
    int video_accurate_seek_fail = 0;
    int64_t video_seek_pos = 0;
    int64_t now = 0;
    int64_t deviation = 0;

    int64_t deviation2 = 0;
    int64_t deviation3 = 0;

    if (ffp->enable_accurate_seek && is->video_accurate_seek_req && !is->seek_req) {
        if (!isnan(pts)) {
            video_seek_pos = is->seek_pos;
            is->accurate_seek_vframe_pts = pts * 1000 * 1000;
            deviation = llabs((int64_t)(pts * 1000 * 1000) - is->seek_pos);
            if ((pts * 1000 * 1000 < is->seek_pos) || deviation > MAX_DEVIATION) {
                now = av_gettime_relative() / 1000;
                if (is->drop_vframe_count == 0) {
                    SDL_LockMutex(is->accurate_seek_mutex);
                    if (is->accurate_seek_start_time <= 0 && (is->audio_stream < 0 || is->audio_accurate_seek_req)) {
                        is->accurate_seek_start_time = now;
                    }
                    SDL_UnlockMutex(is->accurate_seek_mutex);
                    av_log(NULL, AV_LOG_INFO, "video accurate_seek start, is->seek_pos=%lld, pts=%lf, is->accurate_seek_time = %lld\n", is->seek_pos, pts, is->accurate_seek_start_time);
                }
                is->drop_vframe_count++;

                while (is->audio_accurate_seek_req && !is->abort_request) {
                    int64_t apts = is->accurate_seek_aframe_pts ;
                    deviation2 = apts - pts * 1000 * 1000;
                    deviation3 = apts - is->seek_pos;

                    if (deviation2 > -100 * 1000 && deviation3 < 0) {
                        break;
                    } else {
                        av_usleep(20 * 1000);
                    }
                    now = av_gettime_relative() / 1000;
                    if ((now - is->accurate_seek_start_time) > ffp->accurate_seek_timeout) {
                        break;
                    }
                }

                if ((now - is->accurate_seek_start_time) <= ffp->accurate_seek_timeout) {
                    return 1;  // drop some old frame when do accurate seek
                } else {
                    av_log(NULL, AV_LOG_WARNING, "video accurate_seek is error, is->drop_vframe_count=%d, now = %lld, pts = %lf\n", is->drop_vframe_count, now, pts);
                    video_accurate_seek_fail = 1;  // if KEY_FRAME interval too big, disable accurate seek
                }
            } else {
                av_log(NULL, AV_LOG_INFO, "video accurate_seek is ok, is->drop_vframe_count =%d, is->seek_pos=%lld, pts=%lf\n", is->drop_vframe_count, is->seek_pos, pts);
                if (video_seek_pos == is->seek_pos) {
                    is->drop_vframe_count       = 0;
                    SDL_LockMutex(is->accurate_seek_mutex);
                    is->video_accurate_seek_req = 0;
                    SDL_CondSignal(is->audio_accurate_seek_cond);
                    if (video_seek_pos == is->seek_pos && is->audio_accurate_seek_req && !is->abort_request) {
                        SDL_CondWaitTimeout(is->video_accurate_seek_cond, is->accurate_seek_mutex, ffp->accurate_seek_timeout);
                    } else {
                        ffp_notify_msg2(ffp, FFP_MSG_ACCURATE_SEEK_COMPLETE, (int)(pts * 1000));
                    }
                    if (video_seek_pos != is->seek_pos && !is->abort_request) {
                        is->video_accurate_seek_req = 1;
                        SDL_UnlockMutex(is->accurate_seek_mutex);
                        return 1;
                    }

                    SDL_UnlockMutex(is->accurate_seek_mutex);
                }
            }
        } else {
            video_accurate_seek_fail = 1;
        }

        if (video_accurate_seek_fail) {
            is->drop_vframe_count = 0;
            SDL_LockMutex(is->accurate_seek_mutex);
            is->video_accurate_seek_req = 0;
            SDL_CondSignal(is->audio_accurate_seek_cond);
            if (is->audio_accurate_seek_req && !is->abort_request) {
                SDL_CondWaitTimeout(is->video_accurate_seek_cond, is->accurate_seek_mutex, ffp->accurate_seek_timeout);
            } else {
                if (!isnan(pts)) {
                    ffp_notify_msg2(ffp, FFP_MSG_ACCURATE_SEEK_COMPLETE, (int)(pts * 1000));
                } else {
                    ffp_notify_msg2(ffp, FFP_MSG_ACCURATE_SEEK_COMPLETE, 0);
                }
            }
            SDL_UnlockMutex(is->accurate_seek_mutex);
        }
        is->accurate_seek_start_time = 0;
        video_accurate_seek_fail = 0;
        is->accurate_seek_vframe_pts = 0;
    }

#if defined(DEBUG_SYNC)
    printf("frame_type=%c pts=%0.3f\n",
           av_get_picture_type_char(src_frame->pict_type), pts);
#endif

    if (!(vp = frame_queue_peek_writable(&is->pictq)))
        return -1;

    vp->sar = src_frame->sample_aspect_ratio;
#ifdef FFP_MERGE
    vp->uploaded = 0;
#endif

    /* alloc or resize hardware picture buffer */
    if (!vp->bmp || !vp->allocated ||
        vp->width  != src_frame->width ||
        vp->height != src_frame->height ||
        vp->format != src_frame->format) {

        if (vp->width != src_frame->width || vp->height != src_frame->height)
            ffp_notify_msg3(ffp, FFP_MSG_VIDEO_SIZE_CHANGED, src_frame->width, src_frame->height);

        vp->allocated = 0;
        vp->width = src_frame->width;
        vp->height = src_frame->height;
        vp->format = src_frame->format;

        /* the allocation must be done in the main thread to avoid
           locking problems. */
        alloc_picture(ffp, src_frame->format);

        if (is->videoq.abort_request)
            return -1;
    }

    /* if the frame is not skipped, then display it */
    if (vp->bmp) {
        /* get a pointer on the bitmap */
        SDL_VoutLockYUVOverlay(vp->bmp);

#ifdef FFP_MERGE
#if CONFIG_AVFILTER
        // FIXME use direct rendering
        av_image_copy(data, linesize, (const uint8_t **)src_frame->data, src_frame->linesize,
                        src_frame->format, vp->width, vp->height);
#else
        // sws_getCachedContext(...);
#endif
#endif
        // FIXME: set swscale options
        if (SDL_VoutFillFrameYUVOverlay(vp->bmp, src_frame) < 0) {
            av_log(NULL, AV_LOG_FATAL, "Cannot initialize the conversion context\n");
            exit(1);
        }
        /* update the bitmap content */
        SDL_VoutUnlockYUVOverlay(vp->bmp);

        vp->pts = pts;
        vp->duration = duration;
        vp->pos = pos;
        vp->serial = serial;
        vp->sar = src_frame->sample_aspect_ratio;
        vp->bmp->sar_num = vp->sar.num;
        vp->bmp->sar_den = vp->sar.den;

#ifdef FFP_MERGE
        av_frame_move_ref(vp->frame, src_frame);
#endif
        frame_queue_push(&is->pictq);
        if (!is->viddec.first_frame_decoded) {
            ALOGD("Video: first frame decoded\n");
            ffp_notify_msg1(ffp, FFP_MSG_VIDEO_DECODED_START);
            is->viddec.first_frame_decoded_time = SDL_GetTickHR();
            is->viddec.first_frame_decoded = 1;
        }
    }
    return 0;
}