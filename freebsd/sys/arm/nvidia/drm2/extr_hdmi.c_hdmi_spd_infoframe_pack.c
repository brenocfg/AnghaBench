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
typedef  size_t uint8_t ;
struct hdmi_spd_infoframe {size_t length; size_t type; size_t version; size_t sdi; int /*<<< orphan*/  product; int /*<<< orphan*/  vendor; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t ENOSPC ; 
 size_t HDMI_INFOFRAME_HEADER_SIZE ; 
 int /*<<< orphan*/  hdmi_infoframe_set_checksum (void*,size_t) ; 
 int /*<<< orphan*/  memcpy (size_t*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 

ssize_t hdmi_spd_infoframe_pack(struct hdmi_spd_infoframe *frame, void *buffer,
				size_t size)
{
	uint8_t *ptr = buffer;
	size_t length;

	length = HDMI_INFOFRAME_HEADER_SIZE + frame->length;

	if (size < length)
		return -ENOSPC;

	memset(buffer, 0, size);

	ptr[0] = frame->type;
	ptr[1] = frame->version;
	ptr[2] = frame->length;
	ptr[3] = 0; /* checksum */

	/* start infoframe payload */
	ptr += HDMI_INFOFRAME_HEADER_SIZE;

	memcpy(ptr, frame->vendor, sizeof(frame->vendor));
	memcpy(ptr + 8, frame->product, sizeof(frame->product));

	ptr[24] = frame->sdi;

	hdmi_infoframe_set_checksum(buffer, length);

	return length;
}