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
struct TYPE_4__ {float vdps; float vfps; float avdelay; float avdiff; float drop_frame_rate; } ;
struct TYPE_5__ {float pf_playback_rate; float pf_playback_volume; TYPE_1__ stat; } ;
typedef  TYPE_2__ FFPlayer ;

/* Variables and functions */
#define  FFP_PROP_FLOAT_AVDELAY 134 
#define  FFP_PROP_FLOAT_AVDIFF 133 
#define  FFP_PROP_FLOAT_DROP_FRAME_RATE 132 
#define  FFP_PROP_FLOAT_PLAYBACK_RATE 131 
#define  FFP_PROP_FLOAT_PLAYBACK_VOLUME 130 
#define  FFP_PROP_FLOAT_VIDEO_DECODE_FRAMES_PER_SECOND 129 
#define  FFP_PROP_FLOAT_VIDEO_OUTPUT_FRAMES_PER_SECOND 128 

float ffp_get_property_float(FFPlayer *ffp, int id, float default_value)
{
    switch (id) {
        case FFP_PROP_FLOAT_VIDEO_DECODE_FRAMES_PER_SECOND:
            return ffp ? ffp->stat.vdps : default_value;
        case FFP_PROP_FLOAT_VIDEO_OUTPUT_FRAMES_PER_SECOND:
            return ffp ? ffp->stat.vfps : default_value;
        case FFP_PROP_FLOAT_PLAYBACK_RATE:
            return ffp ? ffp->pf_playback_rate : default_value;
        case FFP_PROP_FLOAT_AVDELAY:
            return ffp ? ffp->stat.avdelay : default_value;
        case FFP_PROP_FLOAT_AVDIFF:
            return ffp ? ffp->stat.avdiff : default_value;
        case FFP_PROP_FLOAT_PLAYBACK_VOLUME:
            return ffp ? ffp->pf_playback_volume : default_value;
        case FFP_PROP_FLOAT_DROP_FRAME_RATE:
            return ffp ? ffp->stat.drop_frame_rate : default_value;
        default:
            return default_value;
    }
}