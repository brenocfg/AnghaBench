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
struct getfhat_args {int flags; int /*<<< orphan*/  fhp; int /*<<< orphan*/  path; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int AT_BENEATH ; 
 int AT_SYMLINK_NOFOLLOW ; 
 int EINVAL ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int kern_getfhat (struct thread*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys_getfhat(struct thread *td, struct getfhat_args *uap)
{

	if ((uap->flags & ~(AT_SYMLINK_NOFOLLOW | AT_BENEATH)) != 0)
		return (EINVAL);
	return (kern_getfhat(td, uap->flags, uap->fd, uap->path, UIO_USERSPACE,
	    uap->fhp));
}