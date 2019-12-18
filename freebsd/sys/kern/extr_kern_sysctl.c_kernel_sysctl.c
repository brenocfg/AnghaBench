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
typedef  int /*<<< orphan*/  u_int ;
struct thread {int dummy; } ;
struct sysctl_req {int flags; size_t oldlen; size_t validlen; size_t newlen; scalar_t__ lock; size_t oldidx; void* oldptr; int /*<<< orphan*/  newfunc; int /*<<< orphan*/  oldfunc; void* newptr; struct thread* td; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ REQ_UNWIRED ; 
 scalar_t__ REQ_WIRED ; 
 int /*<<< orphan*/  bzero (struct sysctl_req*,int) ; 
 int /*<<< orphan*/  sysctl_new_kernel ; 
 int /*<<< orphan*/  sysctl_old_kernel ; 
 int sysctl_root (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,struct sysctl_req*) ; 
 int /*<<< orphan*/  vsunlock (void*,size_t) ; 

int
kernel_sysctl(struct thread *td, int *name, u_int namelen, void *old,
    size_t *oldlenp, void *new, size_t newlen, size_t *retval, int flags)
{
	int error = 0;
	struct sysctl_req req;

	bzero(&req, sizeof req);

	req.td = td;
	req.flags = flags;

	if (oldlenp) {
		req.oldlen = *oldlenp;
	}
	req.validlen = req.oldlen;

	if (old) {
		req.oldptr= old;
	}

	if (new != NULL) {
		req.newlen = newlen;
		req.newptr = new;
	}

	req.oldfunc = sysctl_old_kernel;
	req.newfunc = sysctl_new_kernel;
	req.lock = REQ_UNWIRED;

	error = sysctl_root(0, name, namelen, &req);

	if (req.lock == REQ_WIRED && req.validlen > 0)
		vsunlock(req.oldptr, req.validlen);

	if (error && error != ENOMEM)
		return (error);

	if (retval) {
		if (req.oldptr && req.oldidx > req.validlen)
			*retval = req.validlen;
		else
			*retval = req.oldidx;
	}
	return (error);
}