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
struct timeval {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ev; } ;

/* Variables and functions */
 TYPE_1__* AS_MY_EVENT (struct ub_event*) ; 
 int event_add (int /*<<< orphan*/ *,struct timeval*) ; 

__attribute__((used)) static int
my_event_add(struct ub_event* ev, struct timeval* tv)
{
	return event_add(&AS_MY_EVENT(ev)->ev, tv);
}