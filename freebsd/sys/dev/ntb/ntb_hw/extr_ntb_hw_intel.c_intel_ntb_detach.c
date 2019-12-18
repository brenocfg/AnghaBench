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
struct ntb_softc {scalar_t__ type; int /*<<< orphan*/  db_mask_lock; int /*<<< orphan*/  device; int /*<<< orphan*/  peer_msix_work; int /*<<< orphan*/  lr_timer; int /*<<< orphan*/  heartbeat_timer; int /*<<< orphan*/  db_valid_mask; TYPE_1__* self_reg; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  db_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  DB_MASK_LOCK (struct ntb_softc*) ; 
 int /*<<< orphan*/  DB_MASK_UNLOCK (struct ntb_softc*) ; 
 scalar_t__ NTB_XEON ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  db_iowrite (struct ntb_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ntb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ntb_teardown_interrupts (struct ntb_softc*) ; 
 int /*<<< orphan*/  intel_ntb_teardown_xeon (struct ntb_softc*) ; 
 int /*<<< orphan*/  intel_ntb_unmap_pci_bar (struct ntb_softc*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntb_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_busmaster (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
intel_ntb_detach(device_t device)
{
	struct ntb_softc *ntb;

	ntb = device_get_softc(device);

	/* Detach & delete all children */
	ntb_unregister_device(device);

	if (ntb->self_reg != NULL) {
		DB_MASK_LOCK(ntb);
		db_iowrite(ntb, ntb->self_reg->db_mask, ntb->db_valid_mask);
		DB_MASK_UNLOCK(ntb);
	}
	callout_drain(&ntb->heartbeat_timer);
	callout_drain(&ntb->lr_timer);
	callout_drain(&ntb->peer_msix_work);
	pci_disable_busmaster(ntb->device);
	if (ntb->type == NTB_XEON)
		intel_ntb_teardown_xeon(ntb);
	intel_ntb_teardown_interrupts(ntb);

	mtx_destroy(&ntb->db_mask_lock);

	intel_ntb_unmap_pci_bar(ntb);

	return (0);
}