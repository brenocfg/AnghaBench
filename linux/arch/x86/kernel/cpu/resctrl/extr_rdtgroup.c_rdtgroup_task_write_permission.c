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
struct task_struct {int /*<<< orphan*/  pid; } ;
struct kernfs_open_file {int dummy; } ;
struct cred {int /*<<< orphan*/  suid; int /*<<< orphan*/  euid; int /*<<< orphan*/  uid; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 struct cred* current_cred () ; 
 struct cred* get_task_cred (struct task_struct*) ; 
 int /*<<< orphan*/  put_cred (struct cred const*) ; 
 int /*<<< orphan*/  rdt_last_cmd_printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rdtgroup_task_write_permission(struct task_struct *task,
					  struct kernfs_open_file *of)
{
	const struct cred *tcred = get_task_cred(task);
	const struct cred *cred = current_cred();
	int ret = 0;

	/*
	 * Even if we're attaching all tasks in the thread group, we only
	 * need to check permissions on one of them.
	 */
	if (!uid_eq(cred->euid, GLOBAL_ROOT_UID) &&
	    !uid_eq(cred->euid, tcred->uid) &&
	    !uid_eq(cred->euid, tcred->suid)) {
		rdt_last_cmd_printf("No permission to move task %d\n", task->pid);
		ret = -EPERM;
	}

	put_cred(tcred);
	return ret;
}