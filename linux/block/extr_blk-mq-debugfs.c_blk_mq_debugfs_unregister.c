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
struct request_queue {int /*<<< orphan*/ * debugfs_dir; int /*<<< orphan*/ * sched_debugfs_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ *) ; 

void blk_mq_debugfs_unregister(struct request_queue *q)
{
	debugfs_remove_recursive(q->debugfs_dir);
	q->sched_debugfs_dir = NULL;
	q->debugfs_dir = NULL;
}