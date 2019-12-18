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
struct radius_msg {size_t attr_used; } ;
struct radius_attr_hdr {scalar_t__ type; int length; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_memcpy (scalar_t__*,struct radius_attr_hdr*,size_t) ; 
 struct radius_attr_hdr* radius_get_attr_hdr (struct radius_msg*,size_t) ; 

int radius_msg_get_attr(struct radius_msg *msg, u8 type, u8 *buf, size_t len)
{
	struct radius_attr_hdr *attr = NULL, *tmp;
	size_t i, dlen;

	for (i = 0; i < msg->attr_used; i++) {
		tmp = radius_get_attr_hdr(msg, i);
		if (tmp->type == type) {
			attr = tmp;
			break;
		}
	}

	if (!attr || attr->length < sizeof(*attr))
		return -1;

	dlen = attr->length - sizeof(*attr);
	if (buf)
		os_memcpy(buf, (attr + 1), dlen > len ? len : dlen);
	return dlen;
}