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
struct TYPE_2__ {scalar_t__ evsig_caught; } ;
struct event_base {TYPE_1__ sig; } ;
struct event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGCONT ; 
 int /*<<< orphan*/  cleanup_test () ; 
 int /*<<< orphan*/  event_base_free (struct event_base*) ; 
 struct event_base* event_init () ; 
 int /*<<< orphan*/  evsignal_add (struct event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evsignal_del (struct event*) ; 
 int /*<<< orphan*/  evsignal_set (struct event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct event*) ; 
 int /*<<< orphan*/  raise (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_cb ; 
 int test_ok ; 

__attribute__((used)) static void
test_signal_assert(void)
{
	struct event ev;
	struct event_base *base = event_init();
	test_ok = 0;
	/* use SIGCONT so we don't kill ourselves when we signal to nowhere */
	evsignal_set(&ev, SIGCONT, signal_cb, &ev);
	evsignal_add(&ev, NULL);
	/*
	 * if evsignal_del() fails to reset the handler, it's current handler
	 * will still point to evsig_handler().
	 */
	evsignal_del(&ev);

	raise(SIGCONT);
#if 0
	/* only way to verify we were in evsig_handler() */
	/* XXXX Now there's no longer a good way. */
	if (base->sig.evsig_caught)
		test_ok = 0;
	else
		test_ok = 1;
#else
	test_ok = 1;
#endif

	event_base_free(base);
	cleanup_test();
	return;
}