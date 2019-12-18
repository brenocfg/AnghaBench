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
struct event_and_count {int count; } ;
struct event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  event_free (struct event*) ; 

__attribute__((used)) static void
event_finalize_callback_2(struct event *ev, void *arg)
{
	struct event_and_count *evc = arg;
	evc->count += 100;
	event_free(ev);
}