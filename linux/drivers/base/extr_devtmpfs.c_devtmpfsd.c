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
struct req {int /*<<< orphan*/  done; int /*<<< orphan*/  dev; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  mode; int /*<<< orphan*/  name; int /*<<< orphan*/  err; struct req* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLONE_NEWNS ; 
 int /*<<< orphan*/  MS_SILENT ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksys_chdir (char*) ; 
 int /*<<< orphan*/  ksys_chroot (char*) ; 
 int ksys_mount (char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ksys_unshare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  req_lock ; 
 struct req* requests ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  setup_done ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int devtmpfsd(void *p)
{
	int *err = p;
	*err = ksys_unshare(CLONE_NEWNS);
	if (*err)
		goto out;
	*err = ksys_mount("devtmpfs", "/", "devtmpfs", MS_SILENT, NULL);
	if (*err)
		goto out;
	ksys_chdir("/.."); /* will traverse into overmounted root */
	ksys_chroot(".");
	complete(&setup_done);
	while (1) {
		spin_lock(&req_lock);
		while (requests) {
			struct req *req = requests;
			requests = NULL;
			spin_unlock(&req_lock);
			while (req) {
				struct req *next = req->next;
				req->err = handle(req->name, req->mode,
						  req->uid, req->gid, req->dev);
				complete(&req->done);
				req = next;
			}
			spin_lock(&req_lock);
		}
		__set_current_state(TASK_INTERRUPTIBLE);
		spin_unlock(&req_lock);
		schedule();
	}
	return 0;
out:
	complete(&setup_done);
	return *err;
}