#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {float pf_playback_rate; int pf_playback_rate_changed; } ;
typedef  TYPE_1__ FFPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,float) ; 

void ffp_set_playback_rate(FFPlayer *ffp, float rate)
{
    if (!ffp)
        return;

    av_log(ffp, AV_LOG_INFO, "Playback rate: %f\n", rate);
    ffp->pf_playback_rate = rate;
    ffp->pf_playback_rate_changed = 1;
}