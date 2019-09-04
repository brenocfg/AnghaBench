#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_15__ ;
typedef  struct TYPE_18__   TYPE_13__ ;

/* Type definitions */
struct TYPE_21__ {scalar_t__ nb_packets; } ;
struct TYPE_20__ {scalar_t__ serial; } ;
struct TYPE_18__ {scalar_t__ pkt_serial; } ;
struct TYPE_23__ {double frame_last_filter_delay; scalar_t__ continuous_frame_drops_early; int /*<<< orphan*/  frame_drops_early; TYPE_2__ videoq; TYPE_1__ vidclk; TYPE_13__ viddec; TYPE_15__* video_st; int /*<<< orphan*/  ic; } ;
typedef  TYPE_4__ VideoState ;
struct TYPE_25__ {double pts; int /*<<< orphan*/  sample_aspect_ratio; } ;
struct TYPE_22__ {float drop_frame_rate; scalar_t__ decode_frame_count; scalar_t__ drop_frame_count; } ;
struct TYPE_24__ {scalar_t__ framedrop; TYPE_3__ stat; TYPE_4__* is; } ;
struct TYPE_19__ {int /*<<< orphan*/  time_base; } ;
typedef  TYPE_5__ FFPlayer ;
typedef  TYPE_6__ AVFrame ;

/* Variables and functions */
 double AV_NOPTS_VALUE ; 
 scalar_t__ AV_NOSYNC_THRESHOLD ; 
 scalar_t__ AV_SYNC_VIDEO_MASTER ; 
 double NAN ; 
 int /*<<< orphan*/  av_frame_unref (TYPE_6__*) ; 
 int /*<<< orphan*/  av_guess_sample_aspect_ratio (int /*<<< orphan*/ ,TYPE_15__*,TYPE_6__*) ; 
 double av_q2d (int /*<<< orphan*/ ) ; 
 int decoder_decode_frame (TYPE_5__*,TYPE_13__*,TYPE_6__*,int /*<<< orphan*/ *) ; 
 scalar_t__ fabs (double) ; 
 int /*<<< orphan*/  ffp_video_statistic_l (TYPE_5__*) ; 
 double get_master_clock (TYPE_4__*) ; 
 scalar_t__ get_master_sync_type (TYPE_4__*) ; 
 int /*<<< orphan*/  isnan (double) ; 

__attribute__((used)) static int get_video_frame(FFPlayer *ffp, AVFrame *frame)
{
    VideoState *is = ffp->is;
    int got_picture;

    ffp_video_statistic_l(ffp);
    if ((got_picture = decoder_decode_frame(ffp, &is->viddec, frame, NULL)) < 0)
        return -1;

    if (got_picture) {
        double dpts = NAN;

        if (frame->pts != AV_NOPTS_VALUE)
            dpts = av_q2d(is->video_st->time_base) * frame->pts;

        frame->sample_aspect_ratio = av_guess_sample_aspect_ratio(is->ic, is->video_st, frame);

        if (ffp->framedrop>0 || (ffp->framedrop && get_master_sync_type(is) != AV_SYNC_VIDEO_MASTER)) {
            ffp->stat.decode_frame_count++;
            if (frame->pts != AV_NOPTS_VALUE) {
                double diff = dpts - get_master_clock(is);
                if (!isnan(diff) && fabs(diff) < AV_NOSYNC_THRESHOLD &&
                    diff - is->frame_last_filter_delay < 0 &&
                    is->viddec.pkt_serial == is->vidclk.serial &&
                    is->videoq.nb_packets) {
                    is->frame_drops_early++;
                    is->continuous_frame_drops_early++;
                    if (is->continuous_frame_drops_early > ffp->framedrop) {
                        is->continuous_frame_drops_early = 0;
                    } else {
                        ffp->stat.drop_frame_count++;
                        ffp->stat.drop_frame_rate = (float)(ffp->stat.drop_frame_count) / (float)(ffp->stat.decode_frame_count);
                        av_frame_unref(frame);
                        got_picture = 0;
                    }
                }
            }
        }
    }

    return got_picture;
}