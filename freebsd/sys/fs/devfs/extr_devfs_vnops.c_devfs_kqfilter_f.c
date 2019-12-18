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
struct thread {struct file* td_fpop; } ;
struct knote {int dummy; } ;
struct file {int dummy; } ;
struct cdevsw {int (* d_kqfilter ) (struct cdev*,struct knote*) ;} ;
struct cdev {int dummy; } ;

/* Variables and functions */
 struct thread* curthread ; 
 int /*<<< orphan*/  dev_relthread (struct cdev*,int) ; 
 int devfs_fp_check (struct file*,struct cdev**,struct cdevsw**,int*) ; 
 int stub1 (struct cdev*,struct knote*) ; 

__attribute__((used)) static int
devfs_kqfilter_f(struct file *fp, struct knote *kn)
{
	struct cdev *dev;
	struct cdevsw *dsw;
	int error, ref;
	struct file *fpop;
	struct thread *td;

	td = curthread;
	fpop = td->td_fpop;
	error = devfs_fp_check(fp, &dev, &dsw, &ref);
	if (error)
		return (error);
	error = dsw->d_kqfilter(dev, kn);
	td->td_fpop = fpop;
	dev_relthread(dev, ref);
	return (error);
}