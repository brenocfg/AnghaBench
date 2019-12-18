#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_3__* ioctl_dev; TYPE_4__* ifp; } ;
typedef  TYPE_1__ qla_host_t ;
struct TYPE_7__ {int /*<<< orphan*/  if_dunit; } ;
struct TYPE_6__ {TYPE_1__* si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  if_name (TYPE_4__*) ; 
 TYPE_3__* make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla_cdevsw ; 

int
qls_make_cdev(qla_host_t *ha)
{
        ha->ioctl_dev = make_dev(&qla_cdevsw,
				ha->ifp->if_dunit,
                                UID_ROOT,
                                GID_WHEEL,
                                0600,
                                "%s",
                                if_name(ha->ifp));

	if (ha->ioctl_dev == NULL)
		return (-1);

        ha->ioctl_dev->si_drv1 = ha;

	return (0);
}