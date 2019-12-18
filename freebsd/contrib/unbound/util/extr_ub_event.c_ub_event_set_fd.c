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
struct ub_event {int dummy; } ;
struct TYPE_2__ {int ev_fd; } ;

/* Variables and functions */
 TYPE_1__* AS_EVENT (struct ub_event*) ; 

void
ub_event_set_fd(struct ub_event* ev, int fd)
{
	AS_EVENT(ev)->ev_fd = fd;
}