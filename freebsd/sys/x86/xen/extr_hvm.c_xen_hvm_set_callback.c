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
typedef  scalar_t__ u_int ;
struct xen_hvm_param {int value; int /*<<< orphan*/  index; int /*<<< orphan*/  domid; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOMID_SELF ; 
 int /*<<< orphan*/  HVMOP_set_param ; 
 int HVM_CALLBACK_GSI (int) ; 
 int HVM_CALLBACK_PCI_INTX (scalar_t__,scalar_t__) ; 
 int HVM_CALLBACK_VECTOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HVM_PARAM_CALLBACK_IRQ ; 
 int HYPERVISOR_hvm_op (int /*<<< orphan*/ ,struct xen_hvm_param*) ; 
 int /*<<< orphan*/  IDT_EVTCHN ; 
 int /*<<< orphan*/  XENFEAT_hvm_callback_vector ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 scalar_t__ pci_get_intpin (int /*<<< orphan*/ *) ; 
 int pci_get_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ pci_get_slot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int set_percpu_callback (int /*<<< orphan*/ ) ; 
 int xen_evtchn_needs_ack ; 
 scalar_t__ xen_feature (int /*<<< orphan*/ ) ; 
 int xen_vector_callback_enabled ; 

void
xen_hvm_set_callback(device_t dev)
{
	struct xen_hvm_param xhp;
	int irq;

	if (xen_vector_callback_enabled)
		return;

	xhp.domid = DOMID_SELF;
	xhp.index = HVM_PARAM_CALLBACK_IRQ;
	if (xen_feature(XENFEAT_hvm_callback_vector) != 0) {
		int error;

		error = set_percpu_callback(0);
		if (error == 0) {
			xen_evtchn_needs_ack = true;
			/* Trick toolstack to think we are enlightened */
			xhp.value = 1;
		} else
			xhp.value = HVM_CALLBACK_VECTOR(IDT_EVTCHN);
		error = HYPERVISOR_hvm_op(HVMOP_set_param, &xhp);
		if (error == 0) {
			xen_vector_callback_enabled = 1;
			return;
		} else if (xen_evtchn_needs_ack)
			panic("Unable to setup fake HVM param: %d", error);

		printf("Xen HVM callback vector registration failed (%d). "
		    "Falling back to emulated device interrupt\n", error);
	}
	xen_vector_callback_enabled = 0;
	if (dev == NULL) {
		/*
		 * Called from early boot or resume.
		 * xenpci will invoke us again later.
		 */
		return;
	}

	irq = pci_get_irq(dev);
	if (irq < 16) {
		xhp.value = HVM_CALLBACK_GSI(irq);
	} else {
		u_int slot;
		u_int pin;

		slot = pci_get_slot(dev);
		pin = pci_get_intpin(dev) - 1;
		xhp.value = HVM_CALLBACK_PCI_INTX(slot, pin);
	}

	if (HYPERVISOR_hvm_op(HVMOP_set_param, &xhp) != 0)
		panic("Can't set evtchn callback");
}