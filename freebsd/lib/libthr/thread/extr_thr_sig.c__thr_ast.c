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
struct pthread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  THR_IN_CRITICAL (struct pthread*) ; 
 int /*<<< orphan*/  check_cancel (struct pthread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_deferred_signal (struct pthread*) ; 
 int /*<<< orphan*/  check_suspend (struct pthread*) ; 

void
_thr_ast(struct pthread *curthread)
{

	if (!THR_IN_CRITICAL(curthread)) {
		check_deferred_signal(curthread);
		check_suspend(curthread);
		check_cancel(curthread, NULL);
	}
}