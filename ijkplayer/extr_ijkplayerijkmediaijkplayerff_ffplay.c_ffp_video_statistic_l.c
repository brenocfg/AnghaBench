#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  videoq; int /*<<< orphan*/  video_st; } ;
typedef  TYPE_2__ VideoState ;
struct TYPE_6__ {int /*<<< orphan*/  video_cache; } ;
struct TYPE_8__ {TYPE_1__ stat; TYPE_2__* is; } ;
typedef  TYPE_3__ FFPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  ffp_track_statistic_l (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ffp_video_statistic_l(FFPlayer *ffp)
{
    VideoState *is = ffp->is;
    ffp_track_statistic_l(ffp, is->video_st, &is->videoq, &ffp->stat.video_cache);
}