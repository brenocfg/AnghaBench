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
struct timeval {int dummy; } ;
struct TYPE_2__ {int (* add_signal ) (struct ub_event*,struct timeval*) ;} ;

/* Variables and functions */
 scalar_t__ UB_EVENT_MAGIC ; 
 TYPE_1__ default_event_vmt ; 
 int /*<<< orphan*/  fptr_ok (int) ; 
 int my_signal_add (struct ub_event*,struct timeval*) ; 
 int stub1 (struct ub_event*,struct timeval*) ; 

int
ub_signal_add(struct ub_event* ev, struct timeval* tv)
{
	if (ev->magic == UB_EVENT_MAGIC) {
		fptr_ok(ev->vmt != &default_event_vmt ||
			ev->vmt->add_signal == my_signal_add);
		return (*ev->vmt->add_signal)(ev, tv);
	}
	return -1;
}