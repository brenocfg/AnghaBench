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
struct extattr_list_fd_args {int /*<<< orphan*/  nbytes; int /*<<< orphan*/  data; int /*<<< orphan*/  attrnamespace; int /*<<< orphan*/  fd; } ;
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_FD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AUDIT_ARG_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAP_EXTATTR_LIST ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int extattr_list_vp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int getvnode (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct file**) ; 

int
sys_extattr_list_fd(struct thread *td, struct extattr_list_fd_args *uap)
{
	struct file *fp;
	cap_rights_t rights;
	int error;

	AUDIT_ARG_FD(uap->fd);
	AUDIT_ARG_VALUE(uap->attrnamespace);
	error = getvnode(td, uap->fd,
	    cap_rights_init(&rights, CAP_EXTATTR_LIST), &fp);
	if (error)
		return (error);

	error = extattr_list_vp(fp->f_vnode, uap->attrnamespace, uap->data,
	    uap->nbytes, td);

	fdrop(fp, td);
	return (error);
}