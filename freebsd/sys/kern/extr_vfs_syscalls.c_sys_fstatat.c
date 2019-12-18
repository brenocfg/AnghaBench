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
struct stat {int dummy; } ;
struct fstatat_args {int /*<<< orphan*/  buf; int /*<<< orphan*/  path; int /*<<< orphan*/  fd; int /*<<< orphan*/  flag; } ;
typedef  int /*<<< orphan*/  sb ;

/* Variables and functions */
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int copyout (struct stat*,int /*<<< orphan*/ ,int) ; 
 int kern_statat (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct stat*,int /*<<< orphan*/ *) ; 

int
sys_fstatat(struct thread *td, struct fstatat_args *uap)
{
	struct stat sb;
	int error;

	error = kern_statat(td, uap->flag, uap->fd, uap->path,
	    UIO_USERSPACE, &sb, NULL);
	if (error == 0)
		error = copyout(&sb, uap->buf, sizeof (sb));
	return (error);
}