#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {TYPE_1__* attr; scalar_t__ count; } ;
struct eapol_state_machine {TYPE_2__ radius_class; } ;
struct TYPE_3__ {size_t len; int /*<<< orphan*/ * data; } ;

/* Variables and functions */

u8 * ieee802_1x_get_radius_class(struct eapol_state_machine *sm, size_t *len,
				 int idx)
{
	if (sm == NULL || sm->radius_class.attr == NULL ||
	    idx >= (int) sm->radius_class.count)
		return NULL;

	*len = sm->radius_class.attr[idx].len;
	return sm->radius_class.attr[idx].data;
}