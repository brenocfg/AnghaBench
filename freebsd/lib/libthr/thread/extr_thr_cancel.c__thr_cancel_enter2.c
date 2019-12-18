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
struct pthread {int cancel_point; int /*<<< orphan*/  tid; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTHREAD_CANCELED ; 
 scalar_t__ SHOULD_CANCEL (struct pthread*) ; 
 int /*<<< orphan*/  THR_IN_CRITICAL (struct pthread*) ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  _pthread_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thr_wake (int /*<<< orphan*/ ) ; 

void
_thr_cancel_enter2(struct pthread *curthread, int maycancel)
{
	curthread->cancel_point = 1;
	if (__predict_false(SHOULD_CANCEL(curthread) &&
	    !THR_IN_CRITICAL(curthread))) {
		if (!maycancel)
			thr_wake(curthread->tid);
		else
			_pthread_exit(PTHREAD_CANCELED);
	}
}