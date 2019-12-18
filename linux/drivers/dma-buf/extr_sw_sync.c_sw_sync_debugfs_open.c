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
struct sync_timeline {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct sync_timeline* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int TASK_COMM_LEN ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  get_task_comm (char*,int /*<<< orphan*/ ) ; 
 struct sync_timeline* sync_timeline_create (char*) ; 

__attribute__((used)) static int sw_sync_debugfs_open(struct inode *inode, struct file *file)
{
	struct sync_timeline *obj;
	char task_comm[TASK_COMM_LEN];

	get_task_comm(task_comm, current);

	obj = sync_timeline_create(task_comm);
	if (!obj)
		return -ENOMEM;

	file->private_data = obj;

	return 0;
}