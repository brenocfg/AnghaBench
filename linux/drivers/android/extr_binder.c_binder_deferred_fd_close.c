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
struct binder_task_work_cb {int /*<<< orphan*/  twork; scalar_t__ file; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __close_fd_get_file (int,scalar_t__*) ; 
 int /*<<< orphan*/  binder_do_fd_close ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  init_task_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct binder_task_work_cb*) ; 
 struct binder_task_work_cb* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_work_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void binder_deferred_fd_close(int fd)
{
	struct binder_task_work_cb *twcb;

	twcb = kzalloc(sizeof(*twcb), GFP_KERNEL);
	if (!twcb)
		return;
	init_task_work(&twcb->twork, binder_do_fd_close);
	__close_fd_get_file(fd, &twcb->file);
	if (twcb->file)
		task_work_add(current, &twcb->twork, true);
	else
		kfree(twcb);
}