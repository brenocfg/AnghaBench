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
struct sysctl_req {size_t oldlen; scalar_t__ lock; scalar_t__ oldfunc; size_t validlen; scalar_t__ oldptr; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ REQ_WIRED ; 
 scalar_t__ sysctl_old_user ; 
 int vslock (scalar_t__,size_t) ; 

int
sysctl_wire_old_buffer(struct sysctl_req *req, size_t len)
{
	int ret;
	size_t wiredlen;

	wiredlen = (len > 0 && len < req->oldlen) ? len : req->oldlen;
	ret = 0;
	if (req->lock != REQ_WIRED && req->oldptr &&
	    req->oldfunc == sysctl_old_user) {
		if (wiredlen != 0) {
			ret = vslock(req->oldptr, wiredlen);
			if (ret != 0) {
				if (ret != ENOMEM)
					return (ret);
				wiredlen = 0;
			}
		}
		req->lock = REQ_WIRED;
		req->validlen = wiredlen;
	}
	return (0);
}