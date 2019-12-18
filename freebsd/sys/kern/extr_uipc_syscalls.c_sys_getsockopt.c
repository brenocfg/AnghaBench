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
typedef  int /*<<< orphan*/  valsize ;
struct thread {int dummy; } ;
struct getsockopt_args {int /*<<< orphan*/  avalsize; scalar_t__ val; int /*<<< orphan*/  name; int /*<<< orphan*/  level; int /*<<< orphan*/  s; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int kern_getsockopt (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
sys_getsockopt(struct thread *td, struct getsockopt_args *uap)
{
	socklen_t valsize;
	int error;

	if (uap->val) {
		error = copyin(uap->avalsize, &valsize, sizeof (valsize));
		if (error != 0)
			return (error);
	}

	error = kern_getsockopt(td, uap->s, uap->level, uap->name,
	    uap->val, UIO_USERSPACE, &valsize);

	if (error == 0)
		error = copyout(&valsize, uap->avalsize, sizeof (valsize));
	return (error);
}