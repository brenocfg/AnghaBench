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
struct ntb_softc {int allocated_interrupts; int /*<<< orphan*/  device; struct ntb_int_info* int_info; } ;
struct ntb_int_info {int /*<<< orphan*/ * res; int /*<<< orphan*/ * tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_ntb_free_msix_vec (struct ntb_softc*) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
intel_ntb_teardown_interrupts(struct ntb_softc *ntb)
{
	struct ntb_int_info *current_int;
	int i;

	for (i = 0; i < ntb->allocated_interrupts; i++) {
		current_int = &ntb->int_info[i];
		if (current_int->tag != NULL)
			bus_teardown_intr(ntb->device, current_int->res,
			    current_int->tag);

		if (current_int->res != NULL)
			bus_release_resource(ntb->device, SYS_RES_IRQ,
			    rman_get_rid(current_int->res), current_int->res);
	}

	intel_ntb_free_msix_vec(ntb);
	pci_release_msi(ntb->device);
}