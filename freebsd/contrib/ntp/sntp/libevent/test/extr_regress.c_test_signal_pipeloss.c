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
struct TYPE_2__ {int* ev_signal_pair; } ;
struct event_base {TYPE_1__ sig; } ;

/* Variables and functions */
 scalar_t__ EBADF ; 
 int /*<<< orphan*/  cleanup_test () ; 
 int close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  event_base_free (struct event_base*) ; 
 struct event_base* event_init () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int test_ok ; 

__attribute__((used)) static void
test_signal_pipeloss(void)
{
	/* make sure that the base1 pipe is closed correctly. */
	struct event_base *base1, *base2;
	int pipe1;
	test_ok = 0;
	base1 = event_init();
	pipe1 = base1->sig.ev_signal_pair[0];
	base2 = event_init();
	event_base_free(base2);
	event_base_free(base1);
	if (close(pipe1) != -1 || errno!=EBADF) {
		/* fd must be closed, so second close gives -1, EBADF */
		printf("signal pipe not closed. ");
		test_ok = 0;
	} else {
		test_ok = 1;
	}
	cleanup_test();
}