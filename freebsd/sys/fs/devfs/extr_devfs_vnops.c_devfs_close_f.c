#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thread {int dummy; } ;
struct file {int /*<<< orphan*/ * f_cdevpriv; } ;
struct TYPE_4__ {struct file* td_fpop; } ;
struct TYPE_3__ {int (* fo_close ) (struct file*,struct thread*) ;} ;

/* Variables and functions */
 TYPE_2__* curthread ; 
 int /*<<< orphan*/  devfs_fpdrop (struct file*) ; 
 int stub1 (struct file*,struct thread*) ; 
 TYPE_1__ vnops ; 

__attribute__((used)) static int
devfs_close_f(struct file *fp, struct thread *td)
{
	int error;
	struct file *fpop;

	/*
	 * NB: td may be NULL if this descriptor is closed due to
	 * garbage collection from a closed UNIX domain socket.
	 */
	fpop = curthread->td_fpop;
	curthread->td_fpop = fp;
	error = vnops.fo_close(fp, td);
	curthread->td_fpop = fpop;

	/*
	 * The f_cdevpriv cannot be assigned non-NULL value while we
	 * are destroying the file.
	 */
	if (fp->f_cdevpriv != NULL)
		devfs_fpdrop(fp);
	return (error);
}