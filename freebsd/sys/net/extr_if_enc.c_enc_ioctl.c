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
typedef  scalar_t__ u_long ;
struct ifnet {int if_flags; int /*<<< orphan*/  if_drv_flags; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int IFF_UP ; 
 scalar_t__ SIOCSIFFLAGS ; 

__attribute__((used)) static int
enc_ioctl(struct ifnet *ifp, u_long cmd, caddr_t data)
{

	if (cmd != SIOCSIFFLAGS)
		return (EINVAL);
	if (ifp->if_flags & IFF_UP)
		ifp->if_drv_flags |= IFF_DRV_RUNNING;
	else
		ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
	return (0);
}