#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct port_info {TYPE_1__* port_cdev; TYPE_2__* ifp; } ;
struct TYPE_4__ {int /*<<< orphan*/  if_dunit; } ;
struct TYPE_3__ {void* si_drv1; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  cxgb_cdevsw ; 
 int /*<<< orphan*/  if_name (TYPE_2__*) ; 
 TYPE_1__* make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cxgb_makedev(struct port_info *pi)
{
	
	pi->port_cdev = make_dev(&cxgb_cdevsw, pi->ifp->if_dunit,
	    UID_ROOT, GID_WHEEL, 0600, "%s", if_name(pi->ifp));
	
	if (pi->port_cdev == NULL)
		return (ENOMEM);

	pi->port_cdev->si_drv1 = (void *)pi;
	
	return (0);
}