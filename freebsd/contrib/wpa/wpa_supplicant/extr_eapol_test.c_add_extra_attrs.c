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
struct radius_msg {int dummy; } ;
struct extra_radius_attr {struct extra_radius_attr* next; } ;

/* Variables and functions */
 scalar_t__ add_extra_attr (struct radius_msg*,struct extra_radius_attr*) ; 

__attribute__((used)) static int add_extra_attrs(struct radius_msg *msg,
			   struct extra_radius_attr *attrs)
{
	struct extra_radius_attr *p;
	for (p = attrs; p; p = p->next) {
		if (add_extra_attr(msg, p) < 0)
			return -1;
	}
	return 0;
}