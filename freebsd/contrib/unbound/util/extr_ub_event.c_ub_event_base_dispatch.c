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
struct ub_event_base {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS_EVENT_BASE (struct ub_event_base*) ; 
 int event_base_dispatch (int /*<<< orphan*/ ) ; 

int
ub_event_base_dispatch(struct ub_event_base* base)
{
	return event_base_dispatch(AS_EVENT_BASE(base));
}