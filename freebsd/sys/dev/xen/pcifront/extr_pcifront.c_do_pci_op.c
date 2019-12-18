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
typedef  scalar_t__ time_t ;
struct xen_pci_op {int err; } ;
struct pcifront_device {int /*<<< orphan*/  sh_info_lock; TYPE_1__* sh_info; int /*<<< orphan*/  evtchn; } ;
typedef  int /*<<< orphan*/  evtchn_port_t ;
struct TYPE_2__ {int /*<<< orphan*/  flags; struct xen_pci_op op; } ;

/* Variables and functions */
 int HYPERVISOR_poll (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  WPRINTF (char*) ; 
 int XEN_PCI_ERR_dev_not_found ; 
 int /*<<< orphan*/  _XEN_PCIF_active ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  clear_evtchn (int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  memcpy (struct xen_pci_op*,struct xen_pci_op*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify_remote_via_evtchn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 scalar_t__ time_uptime ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int
do_pci_op(struct pcifront_device *pdev, struct xen_pci_op *op)
{
	int err = 0;
	struct xen_pci_op *active_op = &pdev->sh_info->op;
	evtchn_port_t port = pdev->evtchn;
	time_t timeout;

	mtx_lock(&pdev->sh_info_lock);

	memcpy(active_op, op, sizeof(struct xen_pci_op));

	/* Go */
	wmb();
	set_bit(_XEN_PCIF_active, (unsigned long *)&pdev->sh_info->flags);
	notify_remote_via_evtchn(port);

	timeout = time_uptime + 2;

	clear_evtchn(port);

	/* Spin while waiting for the answer */
	while (test_bit
	       (_XEN_PCIF_active, (unsigned long *)&pdev->sh_info->flags)) {
		int err = HYPERVISOR_poll(&port, 1, 3 * hz);
		if (err)
			panic("Failed HYPERVISOR_poll: err=%d", err);
		clear_evtchn(port);
		if (time_uptime > timeout) {
			WPRINTF("pciback not responding!!!\n");
			clear_bit(_XEN_PCIF_active,
				  (unsigned long *)&pdev->sh_info->flags);
			err = XEN_PCI_ERR_dev_not_found;
			goto out;
		}
	}

	memcpy(op, active_op, sizeof(struct xen_pci_op));

	err = op->err;
 out:
	mtx_unlock(&pdev->sh_info_lock);
	return err;
}