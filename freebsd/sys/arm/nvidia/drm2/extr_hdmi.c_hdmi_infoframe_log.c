#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int type; } ;
union hdmi_infoframe {int /*<<< orphan*/  vendor; int /*<<< orphan*/  audio; int /*<<< orphan*/  spd; int /*<<< orphan*/  avi; TYPE_1__ any; } ;

/* Variables and functions */
#define  HDMI_INFOFRAME_TYPE_AUDIO 131 
#define  HDMI_INFOFRAME_TYPE_AVI 130 
#define  HDMI_INFOFRAME_TYPE_SPD 129 
#define  HDMI_INFOFRAME_TYPE_VENDOR 128 
 int /*<<< orphan*/  hdmi_audio_infoframe_log (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hdmi_avi_infoframe_log (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hdmi_spd_infoframe_log (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hdmi_vendor_any_infoframe_log (int /*<<< orphan*/ *) ; 

void hdmi_infoframe_log(union hdmi_infoframe *frame)
{
	switch (frame->any.type) {
	case HDMI_INFOFRAME_TYPE_AVI:
		hdmi_avi_infoframe_log(&frame->avi);
		break;
	case HDMI_INFOFRAME_TYPE_SPD:
		hdmi_spd_infoframe_log(&frame->spd);
		break;
	case HDMI_INFOFRAME_TYPE_AUDIO:
		hdmi_audio_infoframe_log(&frame->audio);
		break;
	case HDMI_INFOFRAME_TYPE_VENDOR:
		hdmi_vendor_any_infoframe_log(&frame->vendor);
		break;
	}
}