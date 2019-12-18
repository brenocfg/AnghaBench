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
struct ucma_file {struct file* filp; int /*<<< orphan*/  mut; int /*<<< orphan*/  poll_wait; int /*<<< orphan*/  ctx_list; int /*<<< orphan*/  event_list; int /*<<< orphan*/  close_wq; } ;
struct inode {int dummy; } ;
struct file {struct ucma_file* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/  alloc_ordered_workqueue (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ucma_file*) ; 
 struct ucma_file* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int nonseekable_open (struct inode*,struct file*) ; 

__attribute__((used)) static int ucma_open(struct inode *inode, struct file *filp)
{
	struct ucma_file *file;

	file = kmalloc(sizeof *file, GFP_KERNEL);
	if (!file)
		return -ENOMEM;

	file->close_wq = alloc_ordered_workqueue("ucma_close_id",
						 WQ_MEM_RECLAIM);
	if (!file->close_wq) {
		kfree(file);
		return -ENOMEM;
	}

	INIT_LIST_HEAD(&file->event_list);
	INIT_LIST_HEAD(&file->ctx_list);
	init_waitqueue_head(&file->poll_wait);
	mutex_init(&file->mut);

	filp->private_data = file;
	file->filp = filp;

	return nonseekable_open(inode, filp);
}