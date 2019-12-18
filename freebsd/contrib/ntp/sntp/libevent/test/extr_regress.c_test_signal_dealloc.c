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
struct event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  cleanup_test () ; 
 int /*<<< orphan*/  event_base_free (struct event_base*) ; 
 struct event_base* event_init () ; 
 int /*<<< orphan*/  evsignal_add (struct event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evsignal_del (struct event*) ; 
 int /*<<< orphan*/  evsignal_set (struct event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct event*) ; 
 int /*<<< orphan*/  signal_cb ; 
 int test_ok ; 

__attribute__((used)) static void
test_signal_dealloc(void)
{
	/* make sure that evsignal_event is event_del'ed and pipe closed */
	struct event ev;
	struct event_base *base = event_init();
	evsignal_set(&ev, SIGUSR1, signal_cb, &ev);
	evsignal_add(&ev, NULL);
	evsignal_del(&ev);
	event_base_free(base);
	/* If we got here without asserting, we're fine. */
	test_ok = 1;
	cleanup_test();
}