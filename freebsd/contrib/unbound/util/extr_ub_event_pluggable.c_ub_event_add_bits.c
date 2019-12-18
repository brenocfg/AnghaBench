#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ub_event {scalar_t__ magic; TYPE_1__* vmt; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* add_bits ) (struct ub_event*,short) ;} ;

/* Variables and functions */
 scalar_t__ UB_EVENT_MAGIC ; 
 TYPE_1__ default_event_vmt ; 
 int /*<<< orphan*/  fptr_ok (int) ; 
 int /*<<< orphan*/  my_event_add_bits (struct ub_event*,short) ; 
 int /*<<< orphan*/  stub1 (struct ub_event*,short) ; 

void
ub_event_add_bits(struct ub_event* ev, short bits)
{
	if (ev->magic == UB_EVENT_MAGIC) {
		fptr_ok(ev->vmt != &default_event_vmt ||
			ev->vmt->add_bits == my_event_add_bits);
		(*ev->vmt->add_bits)(ev, bits);
	}
}