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
struct event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVLOOP_NONBLOCK ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  cleanup_test () ; 
 int /*<<< orphan*/  event_loop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evsignal_add (struct event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evsignal_del (struct event*) ; 
 int /*<<< orphan*/  evsignal_set (struct event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct event*) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_cb ; 
 scalar_t__ test_ok ; 

__attribute__((used)) static void
test_immediatesignal(void)
{
	struct event ev;

	test_ok = 0;
	evsignal_set(&ev, SIGUSR1, signal_cb, &ev);
	evsignal_add(&ev, NULL);
	kill(getpid(), SIGUSR1);
	event_loop(EVLOOP_NONBLOCK);
	evsignal_del(&ev);
	cleanup_test();
}