#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct mqfs_node {int mn_mode; int /*<<< orphan*/  mn_gid; int /*<<< orphan*/  mn_uid; } ;
struct file {struct mqfs_node* f_data; } ;
typedef  int mode_t ;
struct TYPE_2__ {int /*<<< orphan*/  mi_lock; } ;

/* Variables and functions */
 int ACCESSPERMS ; 
 int /*<<< orphan*/  VADMIN ; 
 int /*<<< orphan*/  VREG ; 
 TYPE_1__ mqfs_data ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int vaccess (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ucred*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mqf_chmod(struct file *fp, mode_t mode, struct ucred *active_cred,
    struct thread *td)
{
	struct mqfs_node *pn;
	int error;

	error = 0;
	pn = fp->f_data;
	sx_xlock(&mqfs_data.mi_lock);
	error = vaccess(VREG, pn->mn_mode, pn->mn_uid, pn->mn_gid, VADMIN,
	    active_cred, NULL);
	if (error != 0)
		goto out;
	pn->mn_mode = mode & ACCESSPERMS;
out:
	sx_xunlock(&mqfs_data.mi_lock);
	return (error);
}