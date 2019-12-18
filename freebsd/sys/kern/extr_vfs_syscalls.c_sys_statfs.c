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
struct statfs_args {int /*<<< orphan*/  buf; int /*<<< orphan*/  path; } ;
struct statfs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_STATFS ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int copyout (struct statfs*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (struct statfs*,int /*<<< orphan*/ ) ; 
 int kern_statfs (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct statfs*) ; 
 struct statfs* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys_statfs(struct thread *td, struct statfs_args *uap)
{
	struct statfs *sfp;
	int error;

	sfp = malloc(sizeof(struct statfs), M_STATFS, M_WAITOK);
	error = kern_statfs(td, uap->path, UIO_USERSPACE, sfp);
	if (error == 0)
		error = copyout(sfp, uap->buf, sizeof(struct statfs));
	free(sfp, M_STATFS);
	return (error);
}