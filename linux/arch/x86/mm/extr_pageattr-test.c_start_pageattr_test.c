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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  do_pageattr_test ; 
 struct task_struct* kthread_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  wake_up_process (struct task_struct*) ; 

__attribute__((used)) static int start_pageattr_test(void)
{
	struct task_struct *p;

	p = kthread_create(do_pageattr_test, NULL, "pageattr-test");
	if (!IS_ERR(p))
		wake_up_process(p);
	else
		WARN_ON(1);

	return 0;
}