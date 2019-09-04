#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_13__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_19__ {int size; scalar_t__ nb_packets; scalar_t__ abort_request; } ;
struct TYPE_18__ {int size; scalar_t__ nb_packets; scalar_t__ abort_request; } ;
struct TYPE_20__ {scalar_t__ audio_stream; scalar_t__ video_stream; TYPE_11__ videoq; TYPE_10__ audioq; TYPE_9__* buffer_indicator_queue; TYPE_5__* video_st; TYPE_3__* audio_st; } ;
typedef  TYPE_12__ VideoState ;
struct TYPE_30__ {scalar_t__ nb_packets; } ;
struct TYPE_29__ {int current_high_water_mark_in_ms; int high_water_mark_in_bytes; int next_high_water_mark_in_ms; int last_high_water_mark_in_ms; } ;
struct TYPE_27__ {scalar_t__ duration; } ;
struct TYPE_25__ {scalar_t__ duration; } ;
struct TYPE_28__ {TYPE_6__ video_cache; TYPE_4__ audio_cache; } ;
struct TYPE_23__ {scalar_t__ den; scalar_t__ num; } ;
struct TYPE_26__ {TYPE_2__ time_base; } ;
struct TYPE_22__ {scalar_t__ den; scalar_t__ num; } ;
struct TYPE_24__ {TYPE_1__ time_base; } ;
struct TYPE_21__ {TYPE_8__ dcc; scalar_t__ playable_duration_ms; TYPE_7__ stat; TYPE_12__* is; } ;
typedef  TYPE_13__ FFPlayer ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  FFP_MSG_BUFFERING_UPDATE ; 
 scalar_t__ IJKMIN (scalar_t__,scalar_t__) ; 
 scalar_t__ MIN_MIN_FRAMES ; 
 scalar_t__ av_rescale (int,int,int) ; 
 scalar_t__ ffp_get_current_position_l (TYPE_13__*) ; 
 int /*<<< orphan*/  ffp_notify_msg3 (TYPE_13__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ffp_toggle_buffering (TYPE_13__*,int /*<<< orphan*/ ) ; 

void ffp_check_buffering_l(FFPlayer *ffp)
{
    VideoState *is            = ffp->is;
    int hwm_in_ms             = ffp->dcc.current_high_water_mark_in_ms; // use fast water mark for first loading
    int buf_size_percent      = -1;
    int buf_time_percent      = -1;
    int hwm_in_bytes          = ffp->dcc.high_water_mark_in_bytes;
    int need_start_buffering  = 0;
    int audio_time_base_valid = 0;
    int video_time_base_valid = 0;
    int64_t buf_time_position = -1;

    if(is->audio_st)
        audio_time_base_valid = is->audio_st->time_base.den > 0 && is->audio_st->time_base.num > 0;
    if(is->video_st)
        video_time_base_valid = is->video_st->time_base.den > 0 && is->video_st->time_base.num > 0;

    if (hwm_in_ms > 0) {
        int     cached_duration_in_ms = -1;
        int64_t audio_cached_duration = -1;
        int64_t video_cached_duration = -1;

        if (is->audio_st && audio_time_base_valid) {
            audio_cached_duration = ffp->stat.audio_cache.duration;
#ifdef FFP_SHOW_DEMUX_CACHE
            int audio_cached_percent = (int)av_rescale(audio_cached_duration, 1005, hwm_in_ms * 10);
            av_log(ffp, AV_LOG_DEBUG, "audio cache=%%%d milli:(%d/%d) bytes:(%d/%d) packet:(%d/%d)\n", audio_cached_percent,
                  (int)audio_cached_duration, hwm_in_ms,
                  is->audioq.size, hwm_in_bytes,
                  is->audioq.nb_packets, MIN_FRAMES);
#endif
        }

        if (is->video_st && video_time_base_valid) {
            video_cached_duration = ffp->stat.video_cache.duration;
#ifdef FFP_SHOW_DEMUX_CACHE
            int video_cached_percent = (int)av_rescale(video_cached_duration, 1005, hwm_in_ms * 10);
            av_log(ffp, AV_LOG_DEBUG, "video cache=%%%d milli:(%d/%d) bytes:(%d/%d) packet:(%d/%d)\n", video_cached_percent,
                  (int)video_cached_duration, hwm_in_ms,
                  is->videoq.size, hwm_in_bytes,
                  is->videoq.nb_packets, MIN_FRAMES);
#endif
        }

        if (video_cached_duration > 0 && audio_cached_duration > 0) {
            cached_duration_in_ms = (int)IJKMIN(video_cached_duration, audio_cached_duration);
        } else if (video_cached_duration > 0) {
            cached_duration_in_ms = (int)video_cached_duration;
        } else if (audio_cached_duration > 0) {
            cached_duration_in_ms = (int)audio_cached_duration;
        }

        if (cached_duration_in_ms >= 0) {
            buf_time_position = ffp_get_current_position_l(ffp) + cached_duration_in_ms;
            ffp->playable_duration_ms = buf_time_position;

            buf_time_percent = (int)av_rescale(cached_duration_in_ms, 1005, hwm_in_ms * 10);
#ifdef FFP_SHOW_DEMUX_CACHE
            av_log(ffp, AV_LOG_DEBUG, "time cache=%%%d (%d/%d)\n", buf_time_percent, cached_duration_in_ms, hwm_in_ms);
#endif
#ifdef FFP_NOTIFY_BUF_TIME
            ffp_notify_msg3(ffp, FFP_MSG_BUFFERING_TIME_UPDATE, cached_duration_in_ms, hwm_in_ms);
#endif
        }
    }

    int cached_size = is->audioq.size + is->videoq.size;
    if (hwm_in_bytes > 0) {
        buf_size_percent = (int)av_rescale(cached_size, 1005, hwm_in_bytes * 10);
#ifdef FFP_SHOW_DEMUX_CACHE
        av_log(ffp, AV_LOG_DEBUG, "size cache=%%%d (%d/%d)\n", buf_size_percent, cached_size, hwm_in_bytes);
#endif
#ifdef FFP_NOTIFY_BUF_BYTES
        ffp_notify_msg3(ffp, FFP_MSG_BUFFERING_BYTES_UPDATE, cached_size, hwm_in_bytes);
#endif
    }

    int buf_percent = -1;
    if (buf_time_percent >= 0) {
        // alwas depend on cache duration if valid
        if (buf_time_percent >= 100)
            need_start_buffering = 1;
        buf_percent = buf_time_percent;
    } else {
        if (buf_size_percent >= 100)
            need_start_buffering = 1;
        buf_percent = buf_size_percent;
    }

    if (buf_time_percent >= 0 && buf_size_percent >= 0) {
        buf_percent = FFMIN(buf_time_percent, buf_size_percent);
    }
    if (buf_percent) {
#ifdef FFP_SHOW_BUF_POS
        av_log(ffp, AV_LOG_DEBUG, "buf pos=%"PRId64", %%%d\n", buf_time_position, buf_percent);
#endif
        ffp_notify_msg3(ffp, FFP_MSG_BUFFERING_UPDATE, (int)buf_time_position, buf_percent);
    }

    if (need_start_buffering) {
        if (hwm_in_ms < ffp->dcc.next_high_water_mark_in_ms) {
            hwm_in_ms = ffp->dcc.next_high_water_mark_in_ms;
        } else {
            hwm_in_ms *= 2;
        }

        if (hwm_in_ms > ffp->dcc.last_high_water_mark_in_ms)
            hwm_in_ms = ffp->dcc.last_high_water_mark_in_ms;

        ffp->dcc.current_high_water_mark_in_ms = hwm_in_ms;

        if (is->buffer_indicator_queue && is->buffer_indicator_queue->nb_packets > 0) {
            if (   (is->audioq.nb_packets >= MIN_MIN_FRAMES || is->audio_stream < 0 || is->audioq.abort_request)
                && (is->videoq.nb_packets >= MIN_MIN_FRAMES || is->video_stream < 0 || is->videoq.abort_request)) {
                ffp_toggle_buffering(ffp, 0);
            }
        }
    }
}