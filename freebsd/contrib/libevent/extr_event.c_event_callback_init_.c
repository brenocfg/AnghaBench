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
struct event_callback {scalar_t__ evcb_pri; } ;
struct event_base {scalar_t__ nactivequeues; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct event_callback*,int /*<<< orphan*/ ,int) ; 

void
event_callback_init_(struct event_base *base,
    struct event_callback *cb)
{
	memset(cb, 0, sizeof(*cb));
	cb->evcb_pri = base->nactivequeues - 1;
}