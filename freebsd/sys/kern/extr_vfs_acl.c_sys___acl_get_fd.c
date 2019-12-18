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
struct thread {int dummy; } ;
struct file {int /*<<< orphan*/  f_vnode; } ;
struct __acl_get_fd_args {int /*<<< orphan*/  aclp; int /*<<< orphan*/  type; int /*<<< orphan*/  filedes; } ;
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_FD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAP_ACL_GET ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int getvnode (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct file**) ; 
 int vacl_get_acl (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys___acl_get_fd(struct thread *td, struct __acl_get_fd_args *uap)
{
	struct file *fp;
	cap_rights_t rights;
	int error;

	AUDIT_ARG_FD(uap->filedes);
	error = getvnode(td, uap->filedes,
	    cap_rights_init(&rights, CAP_ACL_GET), &fp);
	if (error == 0) {
		error = vacl_get_acl(td, fp->f_vnode, uap->type, uap->aclp);
		fdrop(fp, td);
	}
	return (error);
}