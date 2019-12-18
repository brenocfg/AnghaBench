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
struct radius_attr_hdr {scalar_t__ type; } ;

/* Variables and functions */
 struct radius_attr_hdr* radius_get_attr_hdr (struct radius_msg*,size_t) ; 

u8 radius_msg_find_unlisted_attr(struct radius_msg *msg, u8 *attrs)
{
	size_t i, j;
	struct radius_attr_hdr *attr;

	for (i = 0; i < msg->attr_used; i++) {
		attr = radius_get_attr_hdr(msg, i);

		for (j = 0; attrs[j]; j++) {
			if (attr->type == attrs[j])
				break;
		}

		if (attrs[j] == 0)
			return attr->type; /* unlisted attr */
	}

	return 0;
}