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
struct linux_file {int /*<<< orphan*/ * f_cdev; int /*<<< orphan*/ * f_vnode; int /*<<< orphan*/  f_sigio; int /*<<< orphan*/  f_flags; } ;
struct linux_cdev {int dummy; } ;
struct file_operations {int /*<<< orphan*/  (* release ) (int /*<<< orphan*/ *,struct linux_file*) ;} ;
struct file {int /*<<< orphan*/  f_flag; scalar_t__ f_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int OPW (struct file*,struct thread*,int /*<<< orphan*/ ) ; 
 scalar_t__ file_count (struct linux_file*) ; 
 int /*<<< orphan*/  funsetown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct linux_file*) ; 
 int /*<<< orphan*/  linux_cdev_deref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  linux_drop_fop (struct linux_cdev*) ; 
 int /*<<< orphan*/  linux_get_fop (struct linux_file*,struct file_operations const**,struct linux_cdev**) ; 
 int /*<<< orphan*/  linux_poll_wait_dequeue (struct linux_file*) ; 
 int /*<<< orphan*/  linux_set_current (struct thread*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct linux_file*) ; 
 int /*<<< orphan*/  vdrop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
linux_file_close(struct file *file, struct thread *td)
{
	struct linux_file *filp;
	const struct file_operations *fop;
	struct linux_cdev *ldev;
	int error;

	filp = (struct linux_file *)file->f_data;

	KASSERT(file_count(filp) == 0,
	    ("File refcount(%d) is not zero", file_count(filp)));

	error = 0;
	filp->f_flags = file->f_flag;
	linux_set_current(td);
	linux_poll_wait_dequeue(filp);
	linux_get_fop(filp, &fop, &ldev);
	if (fop->release != NULL)
		error = -OPW(file, td, fop->release(filp->f_vnode, filp));
	funsetown(&filp->f_sigio);
	if (filp->f_vnode != NULL)
		vdrop(filp->f_vnode);
	linux_drop_fop(ldev);
	if (filp->f_cdev != NULL)
		linux_cdev_deref(filp->f_cdev);
	kfree(filp);

	return (error);
}