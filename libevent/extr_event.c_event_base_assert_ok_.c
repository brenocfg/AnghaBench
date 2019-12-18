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
struct event_base {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVBASE_ACQUIRE_LOCK (struct event_base*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVBASE_RELEASE_LOCK (struct event_base*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_base_assert_ok_nolock_ (struct event_base*) ; 
 int /*<<< orphan*/  th_base_lock ; 

void
event_base_assert_ok_(struct event_base *base)
{
	EVBASE_ACQUIRE_LOCK(base, th_base_lock);
	event_base_assert_ok_nolock_(base);
	EVBASE_RELEASE_LOCK(base, th_base_lock);
}