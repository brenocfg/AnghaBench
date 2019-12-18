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
struct sysctl_req {size_t newlen; size_t newidx; scalar_t__ newptr; } ;

/* Variables and functions */
 int EINVAL ; 
 int WARN_GIANTOK ; 
 int WARN_SLEEPOK ; 
 int /*<<< orphan*/  WITNESS_WARN (int,int /*<<< orphan*/ *,char*) ; 
 int copyin (char const*,void*,size_t) ; 

__attribute__((used)) static int
sysctl_new_user(struct sysctl_req *req, void *p, size_t l)
{
	int error;

	if (!req->newptr)
		return (0);
	if (req->newlen - req->newidx < l)
		return (EINVAL);
	WITNESS_WARN(WARN_GIANTOK | WARN_SLEEPOK, NULL,
	    "sysctl_new_user()");
	error = copyin((const char *)req->newptr + req->newidx, p, l);
	req->newidx += l;
	return (error);
}