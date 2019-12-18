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
struct xenpci_softc {int /*<<< orphan*/  res_irq; int /*<<< orphan*/  intr_cookie; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_BIND_INTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int BUS_SETUP_INTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_hvm_set_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenpci_intr_filter ; 

__attribute__((used)) static int
xenpci_irq_init(device_t device, struct xenpci_softc *scp)
{
	int error;

	error = BUS_SETUP_INTR(device_get_parent(device), device,
			       scp->res_irq, INTR_MPSAFE|INTR_TYPE_MISC,
			       xenpci_intr_filter, NULL, /*trap_frame*/NULL,
			       &scp->intr_cookie);
	if (error)
		return error;

#ifdef SMP
	/*
	 * When using the PCI event delivery callback we cannot assign
	 * events to specific vCPUs, so all events are delivered to vCPU#0 by
	 * Xen. Since the PCI interrupt can fire on any CPU by default, we
	 * need to bind it to vCPU#0 in order to ensure that
	 * xen_intr_handle_upcall always gets called on vCPU#0.
	 */
	error = BUS_BIND_INTR(device_get_parent(device), device,
	                      scp->res_irq, 0);
	if (error)
		return error;
#endif

	xen_hvm_set_callback(device);
	return (0);
}