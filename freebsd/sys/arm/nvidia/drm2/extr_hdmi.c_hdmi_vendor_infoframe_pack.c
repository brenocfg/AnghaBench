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
struct hdmi_vendor_infoframe {size_t vic; int s3d_struct; int length; int type; int version; int s3d_ext_data; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t ENOSPC ; 
 int HDMI_3D_STRUCTURE_INVALID ; 
 int HDMI_3D_STRUCTURE_SIDE_BY_SIDE_HALF ; 
 size_t HDMI_INFOFRAME_HEADER_SIZE ; 
 int /*<<< orphan*/  hdmi_infoframe_set_checksum (void*,size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 

ssize_t hdmi_vendor_infoframe_pack(struct hdmi_vendor_infoframe *frame,
				 void *buffer, size_t size)
{
	uint8_t *ptr = buffer;
	size_t length;

	/* empty info frame */
	if (frame->vic == 0 && frame->s3d_struct == HDMI_3D_STRUCTURE_INVALID)
		return -EINVAL;

	/* only one of those can be supplied */
	if (frame->vic != 0 && frame->s3d_struct != HDMI_3D_STRUCTURE_INVALID)
		return -EINVAL;

	/* for side by side (half) we also need to provide 3D_Ext_Data */
	if (frame->s3d_struct >= HDMI_3D_STRUCTURE_SIDE_BY_SIDE_HALF)
		frame->length = 6;
	else
		frame->length = 5;

	length = HDMI_INFOFRAME_HEADER_SIZE + frame->length;

	if (size < length)
		return -ENOSPC;

	memset(buffer, 0, size);

	ptr[0] = frame->type;
	ptr[1] = frame->version;
	ptr[2] = frame->length;
	ptr[3] = 0; /* checksum */

	/* HDMI OUI */
	ptr[4] = 0x03;
	ptr[5] = 0x0c;
	ptr[6] = 0x00;

	if (frame->vic) {
		ptr[7] = 0x1 << 5;	/* video format */
		ptr[8] = frame->vic;
	} else {
		ptr[7] = 0x2 << 5;	/* video format */
		ptr[8] = (frame->s3d_struct & 0xf) << 4;
		if (frame->s3d_struct >= HDMI_3D_STRUCTURE_SIDE_BY_SIDE_HALF)
			ptr[9] = (frame->s3d_ext_data & 0xf) << 4;
	}

	hdmi_infoframe_set_checksum(buffer, length);

	return length;
}