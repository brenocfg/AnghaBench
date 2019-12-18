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
struct linux_file {int /*<<< orphan*/  f_mode; int /*<<< orphan*/  f_vnode; struct linux_cdev* f_cdev; struct file* _file; int /*<<< orphan*/  f_flags; int /*<<< orphan*/  f_op; int /*<<< orphan*/  f_dentry_store; int /*<<< orphan*/ * f_dentry; } ;
struct linux_cdev {int /*<<< orphan*/  refs; int /*<<< orphan*/  ops; } ;
struct file_operations {int (* open ) (int /*<<< orphan*/ ,struct linux_file*) ;} ;
struct file {int /*<<< orphan*/  f_vnode; int /*<<< orphan*/  f_flag; } ;
struct cdev {struct linux_cdev* si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTYPE_DEV ; 
 int ENXIO ; 
 int /*<<< orphan*/  finit (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct linux_file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct linux_file*) ; 
 int /*<<< orphan*/  linux_cdev_deref (struct linux_cdev*) ; 
 int /*<<< orphan*/  linux_drop_fop (struct linux_cdev*) ; 
 struct linux_file* linux_file_alloc () ; 
 int /*<<< orphan*/  linux_get_fop (struct linux_file*,struct file_operations const**,struct linux_cdev**) ; 
 int /*<<< orphan*/  linux_set_current (struct thread*) ; 
 int /*<<< orphan*/  linuxfileops ; 
 int /*<<< orphan*/  refcount_acquire (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,struct linux_file*) ; 
 int /*<<< orphan*/  vhold (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
linux_dev_fdopen(struct cdev *dev, int fflags, struct thread *td,
    struct file *file)
{
	struct linux_cdev *ldev;
	struct linux_file *filp;
	const struct file_operations *fop;
	int error;

	ldev = dev->si_drv1;

	filp = linux_file_alloc();
	filp->f_dentry = &filp->f_dentry_store;
	filp->f_op = ldev->ops;
	filp->f_mode = file->f_flag;
	filp->f_flags = file->f_flag;
	filp->f_vnode = file->f_vnode;
	filp->_file = file;
	refcount_acquire(&ldev->refs);
	filp->f_cdev = ldev;

	linux_set_current(td);
	linux_get_fop(filp, &fop, &ldev);

	if (fop->open != NULL) {
		error = -fop->open(file->f_vnode, filp);
		if (error != 0) {
			linux_drop_fop(ldev);
			linux_cdev_deref(filp->f_cdev);
			kfree(filp);
			return (error);
		}
	}

	/* hold on to the vnode - used for fstat() */
	vhold(filp->f_vnode);

	/* release the file from devfs */
	finit(file, filp->f_mode, DTYPE_DEV, filp, &linuxfileops);
	linux_drop_fop(ldev);
	return (ENXIO);
}