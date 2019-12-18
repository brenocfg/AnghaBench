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
 int /*<<< orphan*/  EVBASE_ACQUIRE_LOCK (struct event_base*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVBASE_RELEASE_LOCK (struct event_base*,int /*<<< orphan*/ ) ; 
 int event_callback_activate_nolock_ (struct event_base*,struct event_callback*) ; 
 int /*<<< orphan*/  th_base_lock ; 

int
event_callback_activate_(struct event_base *base,
    struct event_callback *evcb)
{
	int r;
	EVBASE_ACQUIRE_LOCK(base, th_base_lock);
	r = event_callback_activate_nolock_(base, evcb);
	EVBASE_RELEASE_LOCK(base, th_base_lock);
	return r;
}