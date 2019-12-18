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
struct statfs {int dummy; } ;
struct fstatfs_args {int /*<<< orphan*/  buf; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_STATFS ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int copyout (struct statfs*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (struct statfs*,int /*<<< orphan*/ ) ; 
 int kern_fstatfs (struct thread*,int /*<<< orphan*/ ,struct statfs*) ; 
 struct statfs* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys_fstatfs(struct thread *td, struct fstatfs_args *uap)
{
	struct statfs *sfp;
	int error;

	sfp = malloc(sizeof(struct statfs), M_STATFS, M_WAITOK);
	error = kern_fstatfs(td, uap->fd, sfp);
	if (error == 0)
		error = copyout(sfp, uap->buf, sizeof(struct statfs));
	free(sfp, M_STATFS);
	return (error);
}