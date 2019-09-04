#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_4__ {scalar_t__ show_mode; scalar_t__ force_refresh; int /*<<< orphan*/  paused; int /*<<< orphan*/  abort_request; } ;
typedef  TYPE_1__ VideoState ;
struct TYPE_5__ {TYPE_1__* is; } ;
typedef  TYPE_2__ FFPlayer ;

/* Variables and functions */
 double REFRESH_RATE ; 
 scalar_t__ SHOW_MODE_NONE ; 
 int /*<<< orphan*/  av_usleep (int) ; 
 int /*<<< orphan*/  video_refresh (TYPE_2__*,double*) ; 

__attribute__((used)) static int video_refresh_thread(void *arg)
{
    FFPlayer *ffp = arg;
    VideoState *is = ffp->is;
    double remaining_time = 0.0;
    while (!is->abort_request) {
        if (remaining_time > 0.0)
            av_usleep((int)(int64_t)(remaining_time * 1000000.0));
        remaining_time = REFRESH_RATE;
        if (is->show_mode != SHOW_MODE_NONE && (!is->paused || is->force_refresh))
            video_refresh(ffp, &remaining_time);
    }

    return 0;
}