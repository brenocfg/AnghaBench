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
struct mq_attr {int dummy; } ;
struct kmq_open_args {int flags; int /*<<< orphan*/ * attr; int /*<<< orphan*/  mode; int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  attr ;

/* Variables and functions */
 int EINVAL ; 
 int FFLAGS (int) ; 
 int O_ACCMODE ; 
 int O_CREAT ; 
 int O_EXEC ; 
 int copyin (int /*<<< orphan*/ *,struct mq_attr*,int) ; 
 int kern_kmq_open (struct thread*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct mq_attr*) ; 

int
sys_kmq_open(struct thread *td, struct kmq_open_args *uap)
{
	struct mq_attr attr;
	int flags, error;

	if ((uap->flags & O_ACCMODE) == O_ACCMODE || uap->flags & O_EXEC)
		return (EINVAL);
	flags = FFLAGS(uap->flags);
	if ((flags & O_CREAT) != 0 && uap->attr != NULL) {
		error = copyin(uap->attr, &attr, sizeof(attr));
		if (error)
			return (error);
	}
	return (kern_kmq_open(td, uap->path, flags, uap->mode,
	    uap->attr != NULL ? &attr : NULL));
}