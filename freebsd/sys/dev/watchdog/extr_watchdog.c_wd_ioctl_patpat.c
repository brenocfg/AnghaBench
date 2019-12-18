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
typedef  int u_int ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
 int WD_ACTIVE ; 
 int WD_INTERVAL ; 
 int WD_LASTVAL ; 
 int WD_PASSIVE ; 
 int wdog_kern_pat (int) ; 

__attribute__((used)) static int
wd_ioctl_patpat(caddr_t data)
{
	u_int u;

	u = *(u_int *)data;
	if (u & ~(WD_ACTIVE | WD_PASSIVE | WD_LASTVAL | WD_INTERVAL))
		return (EINVAL);
	if ((u & (WD_ACTIVE | WD_PASSIVE)) == (WD_ACTIVE | WD_PASSIVE))
		return (EINVAL);
	if ((u & (WD_ACTIVE | WD_PASSIVE)) == 0 && ((u & WD_INTERVAL) > 0 ||
	    (u & WD_LASTVAL) != 0))
		return (EINVAL);
	if (u & WD_PASSIVE)
		return (ENOSYS);	/* XXX Not implemented yet */
	u &= ~(WD_ACTIVE | WD_PASSIVE);

	return (wdog_kern_pat(u));
}