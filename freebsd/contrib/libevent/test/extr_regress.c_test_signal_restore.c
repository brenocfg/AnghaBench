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
struct sigaction {int sa_flags; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;
struct event_base {int dummy; } ;
struct event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGUSR1 ; 
 scalar_t__ SIG_ERR ; 
 int /*<<< orphan*/  cleanup_test () ; 
 int /*<<< orphan*/  event_base_free (struct event_base*) ; 
 struct event_base* event_init () ; 
 int /*<<< orphan*/  evsignal_add (struct event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evsignal_del (struct event*) ; 
 int /*<<< orphan*/  evsignal_set (struct event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct event*) ; 
 int /*<<< orphan*/  raise (int /*<<< orphan*/ ) ; 
 int sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 scalar_t__ signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_cb ; 
 int /*<<< orphan*/  signal_cb_sa ; 
 int test_ok ; 

__attribute__((used)) static void
test_signal_restore(void)
{
	struct event ev;
	struct event_base *base = event_init();
#ifdef EVENT__HAVE_SIGACTION
	struct sigaction sa;
#endif

	test_ok = 0;
#ifdef EVENT__HAVE_SIGACTION
	sa.sa_handler = signal_cb_sa;
	sa.sa_flags = 0x0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		goto out;
#else
	if (signal(SIGUSR1, signal_cb_sa) == SIG_ERR)
		goto out;
#endif
	evsignal_set(&ev, SIGUSR1, signal_cb, &ev);
	evsignal_add(&ev, NULL);
	evsignal_del(&ev);

	raise(SIGUSR1);
	/* 1 == signal_cb, 2 == signal_cb_sa, we want our previous handler */
	if (test_ok != 2)
		test_ok = 0;
out:
	event_base_free(base);
	cleanup_test();
	return;
}