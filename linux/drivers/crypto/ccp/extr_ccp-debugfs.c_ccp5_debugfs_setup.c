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
struct dentry {int dummy; } ;
struct ccp_device {char* name; int cmd_q_count; int id; struct dentry* debugfs_instance; struct ccp_device* cmd_q; } ;
struct ccp_cmd_queue {char* name; int cmd_q_count; int id; struct dentry* debugfs_instance; struct ccp_cmd_queue* cmd_q; } ;

/* Variables and functions */
 char* KBUILD_MODNAME ; 
 int MAX_NAME_LEN ; 
 struct dentry* ccp_debugfs_dir ; 
 int /*<<< orphan*/  ccp_debugfs_info_ops ; 
 int /*<<< orphan*/  ccp_debugfs_lock ; 
 int /*<<< orphan*/  ccp_debugfs_queue_ops ; 
 int /*<<< orphan*/  ccp_debugfs_stats_ops ; 
 void* debugfs_create_dir (char*,struct dentry*) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct ccp_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_initialized () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

void ccp5_debugfs_setup(struct ccp_device *ccp)
{
	struct ccp_cmd_queue *cmd_q;
	char name[MAX_NAME_LEN + 1];
	struct dentry *debugfs_q_instance;
	int i;

	if (!debugfs_initialized())
		return;

	mutex_lock(&ccp_debugfs_lock);
	if (!ccp_debugfs_dir)
		ccp_debugfs_dir = debugfs_create_dir(KBUILD_MODNAME, NULL);
	mutex_unlock(&ccp_debugfs_lock);

	ccp->debugfs_instance = debugfs_create_dir(ccp->name, ccp_debugfs_dir);

	debugfs_create_file("info", 0400, ccp->debugfs_instance, ccp,
			    &ccp_debugfs_info_ops);

	debugfs_create_file("stats", 0600, ccp->debugfs_instance, ccp,
			    &ccp_debugfs_stats_ops);

	for (i = 0; i < ccp->cmd_q_count; i++) {
		cmd_q = &ccp->cmd_q[i];

		snprintf(name, MAX_NAME_LEN - 1, "q%d", cmd_q->id);

		debugfs_q_instance =
			debugfs_create_dir(name, ccp->debugfs_instance);

		debugfs_create_file("stats", 0600, debugfs_q_instance, cmd_q,
				    &ccp_debugfs_queue_ops);
	}

	return;
}