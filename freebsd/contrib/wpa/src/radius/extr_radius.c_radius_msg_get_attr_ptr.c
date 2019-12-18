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
 struct radius_attr_hdr* radius_get_attr_hdr (struct radius_msg*,size_t) ; 

int radius_msg_get_attr_ptr(struct radius_msg *msg, u8 type, u8 **buf,
			    size_t *len, const u8 *start)
{
	size_t i;
	struct radius_attr_hdr *attr = NULL, *tmp;

	for (i = 0; i < msg->attr_used; i++) {
		tmp = radius_get_attr_hdr(msg, i);
		if (tmp->type == type &&
		    (start == NULL || (u8 *) tmp > start)) {
			attr = tmp;
			break;
		}
	}

	if (!attr || attr->length < sizeof(*attr))
		return -1;

	*buf = (u8 *) (attr + 1);
	*len = attr->length - sizeof(*attr);
	return 0;
}