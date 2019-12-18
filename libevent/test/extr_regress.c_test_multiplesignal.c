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
struct TYPE_2__ {int tv_usec; scalar_t__ tv_sec; } ;
struct itimerval {TYPE_1__ it_value; } ;
struct event {int dummy; } ;
typedef  int /*<<< orphan*/  itv ;

/* Variables and functions */
 int /*<<< orphan*/  ITIMER_REAL ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  cleanup_test () ; 
 int /*<<< orphan*/  event_dispatch () ; 
 int /*<<< orphan*/  evsignal_add (struct event*,int /*<<< orphan*/ *) ; 
 int evsignal_del (struct event*) ; 
 int /*<<< orphan*/  evsignal_set (struct event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct event*) ; 
 int /*<<< orphan*/  memset (struct itimerval*,int /*<<< orphan*/ ,int) ; 
 int setitimer (int /*<<< orphan*/ ,struct itimerval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_test (char*) ; 
 int /*<<< orphan*/  signal_cb ; 
 scalar_t__ test_ok ; 

__attribute__((used)) static void
test_multiplesignal(void)
{
	struct event ev_one, ev_two;
	struct itimerval itv;

	setup_test("Multiple signal: ");

	evsignal_set(&ev_one, SIGALRM, signal_cb, &ev_one);
	evsignal_add(&ev_one, NULL);

	evsignal_set(&ev_two, SIGALRM, signal_cb, &ev_two);
	evsignal_add(&ev_two, NULL);

	memset(&itv, 0, sizeof(itv));
	itv.it_value.tv_sec = 0;
	itv.it_value.tv_usec = 100000;
	if (setitimer(ITIMER_REAL, &itv, NULL) == -1)
		goto skip_simplesignal;

	event_dispatch();

 skip_simplesignal:
	if (evsignal_del(&ev_one) == -1)
		test_ok = 0;
	if (evsignal_del(&ev_two) == -1)
		test_ok = 0;

	cleanup_test();
}