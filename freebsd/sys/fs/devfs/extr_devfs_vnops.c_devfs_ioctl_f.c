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
typedef  int /*<<< orphan*/  u_long ;
struct ucred {int dummy; } ;
struct thread {struct file* td_fpop; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int (* fo_ioctl ) (struct file*,int /*<<< orphan*/ ,void*,struct ucred*,struct thread*) ;} ;

/* Variables and functions */
 int stub1 (struct file*,int /*<<< orphan*/ ,void*,struct ucred*,struct thread*) ; 
 TYPE_1__ vnops ; 

__attribute__((used)) static int
devfs_ioctl_f(struct file *fp, u_long com, void *data, struct ucred *cred, struct thread *td)
{
	struct file *fpop;
	int error;

	fpop = td->td_fpop;
	td->td_fpop = fp;
	error = vnops.fo_ioctl(fp, com, data, cred, td);
	td->td_fpop = fpop;
	return (error);
}