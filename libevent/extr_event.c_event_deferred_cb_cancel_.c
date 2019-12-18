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
struct event_callback {int dummy; } ;
struct event_base {int dummy; } ;

/* Variables and functions */
 struct event_base* current_base ; 
 int /*<<< orphan*/  event_callback_cancel_ (struct event_base*,struct event_callback*) ; 

void
event_deferred_cb_cancel_(struct event_base *base, struct event_callback *cb)
{
	if (!base)
		base = current_base;
	event_callback_cancel_(base, cb);
}