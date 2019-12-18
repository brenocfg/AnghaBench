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
struct fhstatfs_args {int /*<<< orphan*/  buf; int /*<<< orphan*/  u_fhp; } ;
typedef  int /*<<< orphan*/  fhandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_STATFS ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int copyout (struct statfs*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (struct statfs*,int /*<<< orphan*/ ) ; 
 int kern_fhstatfs (struct thread*,int /*<<< orphan*/ ,struct statfs*) ; 
 struct statfs* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys_fhstatfs(struct thread *td, struct fhstatfs_args *uap)
{
	struct statfs *sfp;
	fhandle_t fh;
	int error;

	error = copyin(uap->u_fhp, &fh, sizeof(fhandle_t));
	if (error != 0)
		return (error);
	sfp = malloc(sizeof(struct statfs), M_STATFS, M_WAITOK);
	error = kern_fhstatfs(td, fh, sfp);
	if (error == 0)
		error = copyout(sfp, uap->buf, sizeof(*sfp));
	free(sfp, M_STATFS);
	return (error);
}