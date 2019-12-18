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
struct nicpf {int /*<<< orphan*/  check_link_mtx; int /*<<< orphan*/  check_link; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 struct nicpf* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nic_unregister_interrupts (struct nicpf*) ; 
 int /*<<< orphan*/  nicpf_free_res (struct nicpf*) ; 
 int /*<<< orphan*/  pci_disable_busmaster (int /*<<< orphan*/ ) ; 
 int pci_iov_detach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nicpf_detach(device_t dev)
{
	struct nicpf *nic;
	int err;

	err = 0;
	nic = device_get_softc(dev);

	callout_drain(&nic->check_link);
	mtx_destroy(&nic->check_link_mtx);

	nic_unregister_interrupts(nic);
	nicpf_free_res(nic);
	pci_disable_busmaster(dev);

#ifdef PCI_IOV
	err = pci_iov_detach(dev);
	if (err != 0)
		device_printf(dev, "SR-IOV in use. Detach first.\n");
#endif
	return (err);
}