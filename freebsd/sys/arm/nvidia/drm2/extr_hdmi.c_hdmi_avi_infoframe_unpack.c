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
struct hdmi_avi_infoframe {int colorspace; int active_aspect; int top_bar; int bottom_bar; int left_bar; int right_bar; int scan_mode; int colorimetry; int picture_aspect; int itc; int extended_colorimetry; int quantization_range; int nups; int video_code; int ycc_quantization_range; int content_type; int pixel_repeat; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVI ; 
 int EINVAL ; 
 int HDMI_AVI_INFOFRAME_SIZE ; 
 int /*<<< orphan*/  HDMI_INFOFRAME_HEADER_SIZE ; 
 int /*<<< orphan*/  HDMI_INFOFRAME_SIZE (int /*<<< orphan*/ ) ; 
 int HDMI_INFOFRAME_TYPE_AVI ; 
 int hdmi_avi_infoframe_init (struct hdmi_avi_infoframe*) ; 
 scalar_t__ hdmi_infoframe_checksum (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdmi_avi_infoframe_unpack(struct hdmi_avi_infoframe *frame,
				     void *buffer)
{
	uint8_t *ptr = buffer;
	int ret;

	if (ptr[0] != HDMI_INFOFRAME_TYPE_AVI ||
	    ptr[1] != 2 ||
	    ptr[2] != HDMI_AVI_INFOFRAME_SIZE)
		return -EINVAL;

	if (hdmi_infoframe_checksum(buffer, HDMI_INFOFRAME_SIZE(AVI)) != 0)
		return -EINVAL;

	ret = hdmi_avi_infoframe_init(frame);
	if (ret)
		return ret;

	ptr += HDMI_INFOFRAME_HEADER_SIZE;

	frame->colorspace = (ptr[0] >> 5) & 0x3;
	if (ptr[0] & 0x10)
		frame->active_aspect = ptr[1] & 0xf;
	if (ptr[0] & 0x8) {
		frame->top_bar = (ptr[5] << 8) + ptr[6];
		frame->bottom_bar = (ptr[7] << 8) + ptr[8];
	}
	if (ptr[0] & 0x4) {
		frame->left_bar = (ptr[9] << 8) + ptr[10];
		frame->right_bar = (ptr[11] << 8) + ptr[12];
	}
	frame->scan_mode = ptr[0] & 0x3;

	frame->colorimetry = (ptr[1] >> 6) & 0x3;
	frame->picture_aspect = (ptr[1] >> 4) & 0x3;
	frame->active_aspect = ptr[1] & 0xf;

	frame->itc = ptr[2] & 0x80 ? true : false;
	frame->extended_colorimetry = (ptr[2] >> 4) & 0x7;
	frame->quantization_range = (ptr[2] >> 2) & 0x3;
	frame->nups = ptr[2] & 0x3;

	frame->video_code = ptr[3] & 0x7f;
	frame->ycc_quantization_range = (ptr[4] >> 6) & 0x3;
	frame->content_type = (ptr[4] >> 4) & 0x3;

	frame->pixel_repeat = ptr[4] & 0xf;

	return 0;
}