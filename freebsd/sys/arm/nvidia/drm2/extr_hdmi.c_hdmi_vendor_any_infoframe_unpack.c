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
struct hdmi_vendor_infoframe {size_t length; int vic; int s3d_struct; int s3d_ext_data; } ;
union hdmi_vendor_any_infoframe {struct hdmi_vendor_infoframe hdmi; } ;
typedef  int uint8_t ;

/* Variables and functions */
 int EINVAL ; 
 int HDMI_3D_STRUCTURE_SIDE_BY_SIDE_HALF ; 
 scalar_t__ HDMI_INFOFRAME_HEADER_SIZE ; 
 int HDMI_INFOFRAME_TYPE_VENDOR ; 
 scalar_t__ hdmi_infoframe_checksum (void*,scalar_t__) ; 
 int hdmi_vendor_infoframe_init (struct hdmi_vendor_infoframe*) ; 

__attribute__((used)) static int
hdmi_vendor_any_infoframe_unpack(union hdmi_vendor_any_infoframe *frame,
				 void *buffer)
{
	uint8_t *ptr = buffer;
	size_t length;
	int ret;
	uint8_t hdmi_video_format;
	struct hdmi_vendor_infoframe *hvf = &frame->hdmi;

	if (ptr[0] != HDMI_INFOFRAME_TYPE_VENDOR ||
	    ptr[1] != 1 ||
	    (ptr[2] != 5 && ptr[2] != 6))
		return -EINVAL;

	length = ptr[2];

	if (hdmi_infoframe_checksum(buffer,
				    HDMI_INFOFRAME_HEADER_SIZE + length) != 0)
		return -EINVAL;

	ptr += HDMI_INFOFRAME_HEADER_SIZE;

	/* HDMI OUI */
	if ((ptr[0] != 0x03) ||
	    (ptr[1] != 0x0c) ||
	    (ptr[2] != 0x00))
		return -EINVAL;

	hdmi_video_format = ptr[3] >> 5;

	if (hdmi_video_format > 0x2)
		return -EINVAL;

	ret = hdmi_vendor_infoframe_init(hvf);
	if (ret)
		return ret;

	hvf->length = length;

	if (hdmi_video_format == 0x1) {
		hvf->vic = ptr[4];
	} else if (hdmi_video_format == 0x2) {
		hvf->s3d_struct = ptr[4] >> 4;
		if (hvf->s3d_struct >= HDMI_3D_STRUCTURE_SIDE_BY_SIDE_HALF) {
			if (length == 6)
				hvf->s3d_ext_data = ptr[5] >> 4;
			else
				return -EINVAL;
		}
	}

	return 0;
}