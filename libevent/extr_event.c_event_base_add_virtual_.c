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
struct event_base {int /*<<< orphan*/  virtual_event_count; int /*<<< orphan*/  virtual_event_count_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVBASE_ACQUIRE_LOCK (struct event_base*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVBASE_RELEASE_LOCK (struct event_base*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_EVENT_COUNT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  th_base_lock ; 

void
event_base_add_virtual_(struct event_base *base)
{
	EVBASE_ACQUIRE_LOCK(base, th_base_lock);
	base->virtual_event_count++;
	MAX_EVENT_COUNT(base->virtual_event_count_max, base->virtual_event_count);
	EVBASE_RELEASE_LOCK(base, th_base_lock);
}