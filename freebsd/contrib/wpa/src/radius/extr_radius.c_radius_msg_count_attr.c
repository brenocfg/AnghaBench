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

int radius_msg_count_attr(struct radius_msg *msg, u8 type, int min_len)
{
	size_t i;
	int count;

	for (count = 0, i = 0; i < msg->attr_used; i++) {
		struct radius_attr_hdr *attr = radius_get_attr_hdr(msg, i);
		if (attr->type == type &&
		    attr->length >= sizeof(struct radius_attr_hdr) + min_len)
			count++;
	}

	return count;
}