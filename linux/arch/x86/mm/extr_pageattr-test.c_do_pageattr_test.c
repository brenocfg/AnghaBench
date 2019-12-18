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

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 scalar_t__ pageattr_test () ; 
 scalar_t__ print ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int) ; 

__attribute__((used)) static int do_pageattr_test(void *__unused)
{
	while (!kthread_should_stop()) {
		schedule_timeout_interruptible(HZ*30);
		if (pageattr_test() < 0)
			break;
		if (print)
			print--;
	}
	return 0;
}