#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  double int64_t ;
struct TYPE_10__ {TYPE_1__* video_st; } ;
typedef  TYPE_2__ VideoState ;
struct TYPE_14__ {TYPE_2__* is; } ;
struct TYPE_13__ {TYPE_4__* opaque; } ;
struct TYPE_12__ {TYPE_6__* ffp; } ;
struct TYPE_11__ {int /*<<< orphan*/  presentationTimeUs; } ;
struct TYPE_9__ {int /*<<< orphan*/  time_base; } ;
typedef  TYPE_3__ SDL_AMediaCodecBufferInfo ;
typedef  TYPE_4__ IJKFF_Pipenode_Opaque ;
typedef  TYPE_5__ IJKFF_Pipenode ;
typedef  TYPE_6__ FFPlayer ;
typedef  int /*<<< orphan*/  AVRational ;

/* Variables and functions */
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 double NAN ; 
 double av_q2d (int /*<<< orphan*/ ) ; 
 double av_rescale_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static double pts_from_buffer_info(IJKFF_Pipenode *node, SDL_AMediaCodecBufferInfo *buffer_info)
{
    IJKFF_Pipenode_Opaque *opaque     = node->opaque;
    FFPlayer              *ffp        = opaque->ffp;
    VideoState            *is         = ffp->is;
    AVRational             tb         = is->video_st->time_base;
    int64_t amc_pts = av_rescale_q(buffer_info->presentationTimeUs, AV_TIME_BASE_Q, is->video_st->time_base);
    double pts = amc_pts < 0 ? NAN : amc_pts * av_q2d(tb);

    return pts;
}