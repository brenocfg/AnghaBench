#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct ifnet {int /*<<< orphan*/  if_drv_flags; } ;
struct TYPE_8__ {struct ifnet* ifp; } ;
typedef  TYPE_1__ qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  QL_DPRINT1 (TYPE_1__*,char*) ; 
 scalar_t__ qlnx_load (TYPE_1__*) ; 
 int /*<<< orphan*/  qlnx_rdma_dev_open (TYPE_1__*) ; 
 int /*<<< orphan*/  qlnx_stop (TYPE_1__*) ; 
 scalar_t__ qlnx_vf_device (TYPE_1__*) ; 

__attribute__((used)) static void
qlnx_init_locked(qlnx_host_t *ha)
{
	struct ifnet	*ifp = ha->ifp;

	QL_DPRINT1(ha, "Driver Initialization start \n");

	qlnx_stop(ha);

	if (qlnx_load(ha) == 0) {

		ifp->if_drv_flags |= IFF_DRV_RUNNING;
		ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;

#ifdef QLNX_ENABLE_IWARP
		if (qlnx_vf_device(ha) != 0) {
			qlnx_rdma_dev_open(ha);
		}
#endif /* #ifdef QLNX_ENABLE_IWARP */
	}

	return;
}