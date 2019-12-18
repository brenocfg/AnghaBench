#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lagg_port {int (* lp_ioctl ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_1__* lp_ifp; } ;
struct ifreq {int ifr_reqcap; } ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_2__ {int if_capenable; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  SIOCSIFCAP ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lagg_setcaps(struct lagg_port *lp, int cap)
{
	struct ifreq ifr;

	if (lp->lp_ifp->if_capenable == cap)
		return (0);
	if (lp->lp_ioctl == NULL)
		return (ENXIO);
	ifr.ifr_reqcap = cap;
	return ((*lp->lp_ioctl)(lp->lp_ifp, SIOCSIFCAP, (caddr_t)&ifr));
}