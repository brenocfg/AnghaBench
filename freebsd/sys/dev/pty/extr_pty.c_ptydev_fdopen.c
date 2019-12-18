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
struct file {int dummy; } ;
struct cdev {int /*<<< orphan*/  si_drv1; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int EBUSY ; 
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  atomic_cmpset_ptr (uintptr_t*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  counted_warning (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  destroy_dev_sched (struct cdev*) ; 
 int /*<<< orphan*/  devtoname (struct cdev*) ; 
 int pts_alloc_external (int,struct thread*,struct file*,struct cdev*,char*) ; 
 int /*<<< orphan*/  pty_warningcnt ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ptydev_fdopen(struct cdev *dev, int fflags, struct thread *td, struct file *fp)
{
	int error;
	char name[6]; /* "ttyXX" */

	if (!atomic_cmpset_ptr((uintptr_t *)&dev->si_drv1, 0, 1))
		return (EBUSY);

	/* Generate device name and create PTY. */
	strlcpy(name, devtoname(dev), sizeof(name));
	name[0] = 't';

	error = pts_alloc_external(fflags & (FREAD|FWRITE), td, fp, dev, name);
	if (error != 0) {
		destroy_dev_sched(dev);
		return (error);
	}

	/* Raise a warning when a legacy PTY has been allocated. */
	counted_warning(&pty_warningcnt, "is using legacy pty devices");

	return (0);
}