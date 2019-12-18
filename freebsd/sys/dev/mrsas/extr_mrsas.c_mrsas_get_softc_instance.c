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
typedef  scalar_t__ u_long ;
struct mrsas_softc {int dummy; } ;
struct mrsas_iocpacket {size_t host_no; } ;
struct cdev {struct mrsas_softc* si_drv1; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_2__ {int max_index; struct mrsas_softc** sc_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MRSAS_FAULT ; 
 scalar_t__ MRSAS_IOC_GET_PCI_INFO ; 
 int /*<<< orphan*/  mrsas_dprint (struct mrsas_softc*,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__ mrsas_mgmt_info ; 
 int /*<<< orphan*/  printf (char*,size_t) ; 

__attribute__((used)) static struct mrsas_softc *
mrsas_get_softc_instance(struct cdev *dev, u_long cmd, caddr_t arg)
{
	struct mrsas_softc *sc = NULL;
	struct mrsas_iocpacket *user_ioc = (struct mrsas_iocpacket *)arg;

	if (cmd == MRSAS_IOC_GET_PCI_INFO) {
		sc = dev->si_drv1;
	} else {
		/*
		 * get the Host number & the softc from data sent by the
		 * Application
		 */
		sc = mrsas_mgmt_info.sc_ptr[user_ioc->host_no];
		if (sc == NULL)
			printf("There is no Controller number %d\n",
			    user_ioc->host_no);
		else if (user_ioc->host_no >= mrsas_mgmt_info.max_index)
			mrsas_dprint(sc, MRSAS_FAULT,
			    "Invalid Controller number %d\n", user_ioc->host_no);
	}

	return sc;
}