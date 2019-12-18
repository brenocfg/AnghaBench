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
struct ub_event_base {int dummy; } ;
struct timeval {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 TYPE_1__* AS_MY_EVENT_BASE (struct ub_event_base*) ; 
 int event_base_loopexit (int /*<<< orphan*/ ,struct timeval*) ; 

__attribute__((used)) static int
my_event_base_loopexit(struct ub_event_base* base, struct timeval* tv)
{
	return event_base_loopexit(AS_MY_EVENT_BASE(base)->base, tv);
}