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
typedef  int uint8_t ;
struct hdmi_audio_infoframe {int channels; int coding_type; int sample_size; int sample_frequency; int coding_type_ext; int channel_allocation; int level_shift_value; int downmix_inhibit; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO ; 
 int EINVAL ; 
 int HDMI_AUDIO_INFOFRAME_SIZE ; 
 int /*<<< orphan*/  HDMI_INFOFRAME_HEADER_SIZE ; 
 int /*<<< orphan*/  HDMI_INFOFRAME_SIZE (int /*<<< orphan*/ ) ; 
 int HDMI_INFOFRAME_TYPE_AUDIO ; 
 int hdmi_audio_infoframe_init (struct hdmi_audio_infoframe*) ; 
 scalar_t__ hdmi_infoframe_checksum (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdmi_audio_infoframe_unpack(struct hdmi_audio_infoframe *frame,
				       void *buffer)
{
	uint8_t *ptr = buffer;
	int ret;

	if (ptr[0] != HDMI_INFOFRAME_TYPE_AUDIO ||
	    ptr[1] != 1 ||
	    ptr[2] != HDMI_AUDIO_INFOFRAME_SIZE) {
		return -EINVAL;
	}

	if (hdmi_infoframe_checksum(buffer, HDMI_INFOFRAME_SIZE(AUDIO)) != 0)
		return -EINVAL;

	ret = hdmi_audio_infoframe_init(frame);
	if (ret)
		return ret;

	ptr += HDMI_INFOFRAME_HEADER_SIZE;

	frame->channels = ptr[0] & 0x7;
	frame->coding_type = (ptr[0] >> 4) & 0xf;
	frame->sample_size = ptr[1] & 0x3;
	frame->sample_frequency = (ptr[1] >> 2) & 0x7;
	frame->coding_type_ext = ptr[2] & 0x1f;
	frame->channel_allocation = ptr[3];
	frame->level_shift_value = (ptr[4] >> 3) & 0xf;
	frame->downmix_inhibit = ptr[4] & 0x80 ? true : false;

	return 0;
}