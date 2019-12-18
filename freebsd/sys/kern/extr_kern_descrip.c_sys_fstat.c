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
typedef  int /*<<< orphan*/  ub ;
struct thread {int dummy; } ;
struct stat {int dummy; } ;
struct fstat_args {int /*<<< orphan*/  sb; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int copyout (struct stat*,int /*<<< orphan*/ ,int) ; 
 int kern_fstat (struct thread*,int /*<<< orphan*/ ,struct stat*) ; 

int
sys_fstat(struct thread *td, struct fstat_args *uap)
{
	struct stat ub;
	int error;

	error = kern_fstat(td, uap->fd, &ub);
	if (error == 0)
		error = copyout(&ub, uap->sb, sizeof(ub));
	return (error);
}