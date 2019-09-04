#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {float pf_playback_volume; int pf_playback_volume_changed; } ;
typedef  TYPE_1__ FFPlayer ;

/* Variables and functions */

void ffp_set_playback_volume(FFPlayer *ffp, float volume)
{
    if (!ffp)
        return;
    ffp->pf_playback_volume = volume;
    ffp->pf_playback_volume_changed = 1;
}