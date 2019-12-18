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
struct vnode {int dummy; } ;
struct thread {int dummy; } ;
struct file {struct vnode* f_vnode; } ;
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 int EINVAL ; 
 int _fget (struct thread*,int,struct file**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int /*<<< orphan*/  vrefact (struct vnode*) ; 

__attribute__((used)) static __inline int
_fgetvp(struct thread *td, int fd, int flags, cap_rights_t *needrightsp,
    struct vnode **vpp)
{
	struct file *fp;
	int error;

	*vpp = NULL;
	error = _fget(td, fd, &fp, flags, needrightsp, NULL);
	if (error != 0)
		return (error);
	if (fp->f_vnode == NULL) {
		error = EINVAL;
	} else {
		*vpp = fp->f_vnode;
		vrefact(*vpp);
	}
	fdrop(fp, td);

	return (error);
}