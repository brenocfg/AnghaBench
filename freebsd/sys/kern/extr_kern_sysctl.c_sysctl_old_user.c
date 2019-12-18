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
struct sysctl_req {size_t oldidx; scalar_t__ lock; size_t validlen; int /*<<< orphan*/ * oldptr; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ REQ_WIRED ; 
 int WARN_GIANTOK ; 
 int WARN_SLEEPOK ; 
 int /*<<< orphan*/  WITNESS_WARN (int,int /*<<< orphan*/ *,char*) ; 
 int copyout (void const*,char*,size_t) ; 
 int copyout_nofault (void const*,char*,size_t) ; 

__attribute__((used)) static int
sysctl_old_user(struct sysctl_req *req, const void *p, size_t l)
{
	size_t i, len, origidx;
	int error;

	origidx = req->oldidx;
	req->oldidx += l;
	if (req->oldptr == NULL)
		return (0);
	/*
	 * If we have not wired the user supplied buffer and we are currently
	 * holding locks, drop a witness warning, as it's possible that
	 * write operations to the user page can sleep.
	 */
	if (req->lock != REQ_WIRED)
		WITNESS_WARN(WARN_GIANTOK | WARN_SLEEPOK, NULL,
		    "sysctl_old_user()");
	i = l;
	len = req->validlen;
	if (len <= origidx)
		i = 0;
	else {
		if (i > len - origidx)
			i = len - origidx;
		if (req->lock == REQ_WIRED) {
			error = copyout_nofault(p, (char *)req->oldptr +
			    origidx, i);
		} else
			error = copyout(p, (char *)req->oldptr + origidx, i);
		if (error != 0)
			return (error);
	}
	if (i < l)
		return (ENOMEM);
	return (0);
}