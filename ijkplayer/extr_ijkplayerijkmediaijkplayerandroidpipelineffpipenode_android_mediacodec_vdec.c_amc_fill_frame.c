#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_2__* video_st; } ;
typedef  TYPE_3__ VideoState ;
struct TYPE_20__ {int /*<<< orphan*/  pts; int /*<<< orphan*/  sample_aspect_ratio; int /*<<< orphan*/  format; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  opaque; } ;
struct TYPE_19__ {TYPE_3__* is; } ;
struct TYPE_18__ {TYPE_5__* opaque; } ;
struct TYPE_17__ {TYPE_1__* codecpar; int /*<<< orphan*/  frame_height; int /*<<< orphan*/  frame_width; int /*<<< orphan*/  weak_vout; TYPE_7__* ffp; } ;
struct TYPE_16__ {int /*<<< orphan*/  presentationTimeUs; } ;
struct TYPE_14__ {int /*<<< orphan*/  time_base; } ;
struct TYPE_13__ {int /*<<< orphan*/  sample_aspect_ratio; } ;
typedef  TYPE_4__ SDL_AMediaCodecBufferInfo ;
typedef  TYPE_5__ IJKFF_Pipenode_Opaque ;
typedef  TYPE_6__ IJKFF_Pipenode ;
typedef  TYPE_7__ FFPlayer ;
typedef  TYPE_8__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 int /*<<< orphan*/  IJK_AV_PIX_FMT__ANDROID_MEDIACODEC ; 
 int /*<<< orphan*/  SDL_VoutAndroid_obtainBufferProxy (int /*<<< orphan*/ ,int,int,TYPE_4__*) ; 
 int /*<<< orphan*/  av_rescale_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amc_fill_frame(
    IJKFF_Pipenode            *node,
    AVFrame                   *frame,
    int                       *got_frame,
    int                        output_buffer_index,
    int                        acodec_serial,
    SDL_AMediaCodecBufferInfo *buffer_info)
{
    IJKFF_Pipenode_Opaque *opaque     = node->opaque;
    FFPlayer              *ffp        = opaque->ffp;
    VideoState            *is         = ffp->is;

    frame->opaque = SDL_VoutAndroid_obtainBufferProxy(opaque->weak_vout, acodec_serial, output_buffer_index, buffer_info);
    if (!frame->opaque)
        goto fail;

    frame->width  = opaque->frame_width;
    frame->height = opaque->frame_height;
    frame->format = IJK_AV_PIX_FMT__ANDROID_MEDIACODEC;
    frame->sample_aspect_ratio = opaque->codecpar->sample_aspect_ratio;
    frame->pts    = av_rescale_q(buffer_info->presentationTimeUs, AV_TIME_BASE_Q, is->video_st->time_base);
    if (frame->pts < 0)
        frame->pts = AV_NOPTS_VALUE;
    // ALOGE("%s: %f", __func__, (float)frame->pts);

    *got_frame = 1;
    return 0;
fail:
    *got_frame = 0;
    return -1;
}