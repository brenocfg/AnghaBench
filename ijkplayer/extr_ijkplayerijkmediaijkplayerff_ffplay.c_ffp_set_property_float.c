#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  FFPlayer ;

/* Variables and functions */
#define  FFP_PROP_FLOAT_PLAYBACK_RATE 129 
#define  FFP_PROP_FLOAT_PLAYBACK_VOLUME 128 
 int /*<<< orphan*/  ffp_set_playback_rate (int /*<<< orphan*/ *,float) ; 
 int /*<<< orphan*/  ffp_set_playback_volume (int /*<<< orphan*/ *,float) ; 

void ffp_set_property_float(FFPlayer *ffp, int id, float value)
{
    switch (id) {
        case FFP_PROP_FLOAT_PLAYBACK_RATE:
            ffp_set_playback_rate(ffp, value);
            break;
        case FFP_PROP_FLOAT_PLAYBACK_VOLUME:
            ffp_set_playback_volume(ffp, value);
            break;
        default:
            return;
    }
}