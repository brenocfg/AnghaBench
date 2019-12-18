#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; int /*<<< orphan*/  task_list; int /*<<< orphan*/  func; int /*<<< orphan*/  private; } ;
typedef  TYPE_1__ wait_queue_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  autoremove_wake_function ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
linux_init_wait_entry(wait_queue_t *wq, int flags)
{

	memset(wq, 0, sizeof(*wq));
	wq->flags = flags;
	wq->private = current;
	wq->func = autoremove_wake_function;
	INIT_LIST_HEAD(&wq->task_list);
}