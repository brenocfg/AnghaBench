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
struct sysctl_req {int flags; size_t oldlen; size_t validlen; size_t newlen; scalar_t__ lock; size_t oldidx; void* oldptr; scalar_t__ newidx; int /*<<< orphan*/  newfunc; int /*<<< orphan*/  oldfunc; void const* newptr; struct thread* td; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int ENOMEM ; 
 scalar_t__ KTRPOINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_SYSCTL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PRI_USER ; 
 scalar_t__ REQ_UNWIRED ; 
 scalar_t__ REQ_WIRED ; 
 int /*<<< orphan*/  TD_TO_VNET (struct thread*) ; 
 int /*<<< orphan*/  bzero (struct sysctl_req*,int) ; 
 int copyin (size_t*,size_t*,int) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  kern_yield (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktrsysctl (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysctl_new_user ; 
 int /*<<< orphan*/  sysctl_old_user ; 
 int sysctl_root (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,struct sysctl_req*) ; 
 int /*<<< orphan*/  sysctlmemlock ; 
 int /*<<< orphan*/  vsunlock (void*,size_t) ; 

int
userland_sysctl(struct thread *td, int *name, u_int namelen, void *old,
    size_t *oldlenp, int inkernel, const void *new, size_t newlen,
    size_t *retval, int flags)
{
	int error = 0, memlocked;
	struct sysctl_req req;

	bzero(&req, sizeof req);

	req.td = td;
	req.flags = flags;

	if (oldlenp) {
		if (inkernel) {
			req.oldlen = *oldlenp;
		} else {
			error = copyin(oldlenp, &req.oldlen, sizeof(*oldlenp));
			if (error)
				return (error);
		}
	}
	req.validlen = req.oldlen;
	req.oldptr = old;

	if (new != NULL) {
		req.newlen = newlen;
		req.newptr = new;
	}

	req.oldfunc = sysctl_old_user;
	req.newfunc = sysctl_new_user;
	req.lock = REQ_UNWIRED;

#ifdef KTRACE
	if (KTRPOINT(curthread, KTR_SYSCTL))
		ktrsysctl(name, namelen);
#endif
	memlocked = 0;
	if (req.oldptr && req.oldlen > 4 * PAGE_SIZE) {
		memlocked = 1;
		sx_xlock(&sysctlmemlock);
	}
	CURVNET_SET(TD_TO_VNET(td));

	for (;;) {
		req.oldidx = 0;
		req.newidx = 0;
		error = sysctl_root(0, name, namelen, &req);
		if (error != EAGAIN)
			break;
		kern_yield(PRI_USER);
	}

	CURVNET_RESTORE();

	if (req.lock == REQ_WIRED && req.validlen > 0)
		vsunlock(req.oldptr, req.validlen);
	if (memlocked)
		sx_xunlock(&sysctlmemlock);

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