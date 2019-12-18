#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int step; scalar_t__ paused; } ;
typedef  TYPE_1__ VideoState ;
struct TYPE_6__ {TYPE_1__* is; } ;
typedef  TYPE_2__ FFPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  stream_toggle_pause_l (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void step_to_next_frame_l(FFPlayer *ffp)
{
    VideoState *is = ffp->is;
    is->step = 1;
    /* if the stream is paused unpause it, then step */
    if (is->paused)
        stream_toggle_pause_l(ffp, 0);
}