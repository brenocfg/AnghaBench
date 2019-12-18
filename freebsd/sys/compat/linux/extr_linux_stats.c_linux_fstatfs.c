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
struct linux_fstatfs_args {int /*<<< orphan*/  buf; int /*<<< orphan*/  fd; } ;
struct l_statfs {int dummy; } ;
typedef  int /*<<< orphan*/  linux_statfs ;

/* Variables and functions */
 int /*<<< orphan*/  M_STATFS ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int bsd_to_linux_statfs (struct statfs*,struct l_statfs*) ; 
 int copyout (struct l_statfs*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (struct statfs*,int /*<<< orphan*/ ) ; 
 int kern_fstatfs (struct thread*,int /*<<< orphan*/ ,struct statfs*) ; 
 struct statfs* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
linux_fstatfs(struct thread *td, struct linux_fstatfs_args *args)
{
	struct l_statfs linux_statfs;
	struct statfs *bsd_statfs;
	int error;

	bsd_statfs = malloc(sizeof(struct statfs), M_STATFS, M_WAITOK);
	error = kern_fstatfs(td, args->fd, bsd_statfs);
	if (error == 0)
		error = bsd_to_linux_statfs(bsd_statfs, &linux_statfs);
	free(bsd_statfs, M_STATFS);
	if (error != 0)
		return (error);
	return (copyout(&linux_statfs, args->buf, sizeof(linux_statfs)));
}