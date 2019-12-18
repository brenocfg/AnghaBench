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
typedef  int /*<<< orphan*/  ub32 ;
struct thread {int dummy; } ;
struct stat32 {int dummy; } ;
struct stat {int dummy; } ;
struct freebsd32_fstatat_args {int /*<<< orphan*/  buf; int /*<<< orphan*/  path; int /*<<< orphan*/  fd; int /*<<< orphan*/  flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int /*<<< orphan*/  copy_stat (struct stat*,struct stat32*) ; 
 int copyout (struct stat32*,int /*<<< orphan*/ ,int) ; 
 int kern_statat (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct stat*,int /*<<< orphan*/ *) ; 

int
freebsd32_fstatat(struct thread *td, struct freebsd32_fstatat_args *uap)
{
	struct stat ub;
	struct stat32 ub32;
	int error;

	error = kern_statat(td, uap->flag, uap->fd, uap->path, UIO_USERSPACE,
	    &ub, NULL);
	if (error)
		return (error);
	copy_stat(&ub, &ub32);
	error = copyout(&ub32, uap->buf, sizeof(ub32));
	return (error);
}