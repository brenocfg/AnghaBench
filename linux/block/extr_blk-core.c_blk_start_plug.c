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
struct task_struct {struct blk_plug* plug; } ;
struct blk_plug {int multiple_queues; scalar_t__ rq_count; int /*<<< orphan*/  cb_list; int /*<<< orphan*/  mq_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct task_struct* current ; 

void blk_start_plug(struct blk_plug *plug)
{
	struct task_struct *tsk = current;

	/*
	 * If this is a nested plug, don't actually assign it.
	 */
	if (tsk->plug)
		return;

	INIT_LIST_HEAD(&plug->mq_list);
	INIT_LIST_HEAD(&plug->cb_list);
	plug->rq_count = 0;
	plug->multiple_queues = false;

	/*
	 * Store ordering should not be needed here, since a potential
	 * preempt will imply a full memory barrier
	 */
	tsk->plug = plug;
}