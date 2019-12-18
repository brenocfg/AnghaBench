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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct radius_msg {size_t attr_used; } ;
struct radius_attr_vendor {size_t vendor_length; scalar_t__ vendor_type; } ;
struct radius_attr_hdr {scalar_t__ type; int length; } ;

/* Variables and functions */
 scalar_t__ RADIUS_ATTR_VENDOR_SPECIFIC ; 
 scalar_t__ ntohl (scalar_t__) ; 
 int /*<<< orphan*/  os_memcpy (scalar_t__*,scalar_t__*,int) ; 
 scalar_t__* os_memdup (scalar_t__*,size_t) ; 
 struct radius_attr_hdr* radius_get_attr_hdr (struct radius_msg*,size_t) ; 

__attribute__((used)) static u8 *radius_msg_get_vendor_attr(struct radius_msg *msg, u32 vendor,
				      u8 subtype, size_t *alen)
{
	u8 *data, *pos;
	size_t i, len;

	if (msg == NULL)
		return NULL;

	for (i = 0; i < msg->attr_used; i++) {
		struct radius_attr_hdr *attr = radius_get_attr_hdr(msg, i);
		size_t left;
		u32 vendor_id;
		struct radius_attr_vendor *vhdr;

		if (attr->type != RADIUS_ATTR_VENDOR_SPECIFIC ||
		    attr->length < sizeof(*attr))
			continue;

		left = attr->length - sizeof(*attr);
		if (left < 4)
			continue;

		pos = (u8 *) (attr + 1);

		os_memcpy(&vendor_id, pos, 4);
		pos += 4;
		left -= 4;

		if (ntohl(vendor_id) != vendor)
			continue;

		while (left >= sizeof(*vhdr)) {
			vhdr = (struct radius_attr_vendor *) pos;
			if (vhdr->vendor_length > left ||
			    vhdr->vendor_length < sizeof(*vhdr)) {
				break;
			}
			if (vhdr->vendor_type != subtype) {
				pos += vhdr->vendor_length;
				left -= vhdr->vendor_length;
				continue;
			}

			len = vhdr->vendor_length - sizeof(*vhdr);
			data = os_memdup(pos + sizeof(*vhdr), len);
			if (data == NULL)
				return NULL;
			if (alen)
				*alen = len;
			return data;
		}
	}

	return NULL;
}