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
struct thread {size_t* td_retval; } ;
struct getfsstat_args {scalar_t__ bufsize; int /*<<< orphan*/  mode; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SIZE_MAX ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int kern_getfsstat (struct thread*,int /*<<< orphan*/ *,scalar_t__,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys_getfsstat(struct thread *td, struct getfsstat_args *uap)
{
	size_t count;
	int error;

	if (uap->bufsize < 0 || uap->bufsize > SIZE_MAX)
		return (EINVAL);
	error = kern_getfsstat(td, &uap->buf, uap->bufsize, &count,
	    UIO_USERSPACE, uap->mode);
	if (error == 0)
		td->td_retval[0] = count;
	return (error);
}