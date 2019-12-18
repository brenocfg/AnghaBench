#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ isp_nirq; int /*<<< orphan*/  isp_lock; } ;
struct isp_sbussoftc {int /*<<< orphan*/  regs; int /*<<< orphan*/  rgd; int /*<<< orphan*/  irq; int /*<<< orphan*/  iqd; int /*<<< orphan*/  ih; TYPE_1__ sbus_isp; } ;
typedef  TYPE_1__ ispsoftc_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  ISP_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct isp_sbussoftc* device_get_softc (int /*<<< orphan*/ ) ; 
 int isp_detach (TYPE_1__*) ; 
 int /*<<< orphan*/  isp_sbus_mbxdmafree (TYPE_1__*) ; 
 int /*<<< orphan*/  isp_shutdown (TYPE_1__*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
isp_sbus_detach(device_t dev)
{
	struct isp_sbussoftc *sbs = device_get_softc(dev);
	ispsoftc_t *isp = &sbs->sbus_isp;
	int status;

	status = isp_detach(isp);
	if (status)
		return (status);
	ISP_LOCK(isp);
	isp_shutdown(isp);
	ISP_UNLOCK(isp);
	if (isp->isp_nirq > 0) {
		(void) bus_teardown_intr(dev, sbs->irq, sbs->ih);
		(void) bus_release_resource(dev, SYS_RES_IRQ, sbs->iqd,
		    sbs->irq);
	}
	(void) bus_release_resource(dev, SYS_RES_MEMORY, sbs->rgd, sbs->regs);
	isp_sbus_mbxdmafree(isp);
	mtx_destroy(&isp->isp_lock);
	return (0);
}