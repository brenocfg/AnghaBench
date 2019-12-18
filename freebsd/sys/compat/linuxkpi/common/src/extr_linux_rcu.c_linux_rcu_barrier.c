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
struct linux_epoch_head {int /*<<< orphan*/  task; } ;

/* Variables and functions */
 struct linux_epoch_head linux_epoch_head ; 
 int /*<<< orphan*/  linux_synchronize_rcu () ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_fast ; 

void
linux_rcu_barrier(void)
{
	struct linux_epoch_head *head;

	linux_synchronize_rcu();

	head = &linux_epoch_head;

	/* wait for callbacks to complete */
	taskqueue_drain(taskqueue_fast, &head->task);
}