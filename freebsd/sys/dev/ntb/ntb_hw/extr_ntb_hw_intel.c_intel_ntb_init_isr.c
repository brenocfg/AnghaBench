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
typedef  int uint32_t ;
struct ntb_softc {scalar_t__ type; int db_vec_count; int /*<<< orphan*/  device; int /*<<< orphan*/  db_vec_shift; int /*<<< orphan*/  db_count; int /*<<< orphan*/  db_mask; TYPE_1__* self_reg; int /*<<< orphan*/  db_valid_mask; int /*<<< orphan*/  last_ts; scalar_t__ allocated_interrupts; } ;
struct TYPE_2__ {int /*<<< orphan*/  db_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  DB_MASK_LOCK (struct ntb_softc*) ; 
 int /*<<< orphan*/  DB_MASK_UNLOCK (struct ntb_softc*) ; 
 int EINVAL ; 
 scalar_t__ HAS_FEATURE (struct ntb_softc*,int /*<<< orphan*/ ) ; 
 int MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NTB_SB01BASE_LOCKUP ; 
 scalar_t__ NTB_XEON ; 
 int /*<<< orphan*/  XEON_DB_TOTAL_SHIFT ; 
 int XEON_NONLINK_DB_MSIX_BITS ; 
 int /*<<< orphan*/  db_iowrite (struct ntb_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  intel_ntb_create_msix_vec (struct ntb_softc*,int) ; 
 int /*<<< orphan*/  intel_ntb_free_msix_vec (struct ntb_softc*) ; 
 int intel_ntb_remap_msix (int /*<<< orphan*/ ,int,int) ; 
 int intel_ntb_setup_legacy_interrupt (struct ntb_softc*) ; 
 int intel_ntb_setup_msix (struct ntb_softc*,int) ; 
 scalar_t__ ntb_force_remap_mode ; 
 int pci_alloc_msix (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_msix_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ticks ; 

__attribute__((used)) static int
intel_ntb_init_isr(struct ntb_softc *ntb)
{
	uint32_t desired_vectors, num_vectors;
	int rc;

	ntb->allocated_interrupts = 0;
	ntb->last_ts = ticks;

	/*
	 * Mask all doorbell interrupts.  (Except link events!)
	 */
	DB_MASK_LOCK(ntb);
	ntb->db_mask = ntb->db_valid_mask;
	db_iowrite(ntb, ntb->self_reg->db_mask, ntb->db_mask);
	DB_MASK_UNLOCK(ntb);

	num_vectors = desired_vectors = MIN(pci_msix_count(ntb->device),
	    ntb->db_count);
	if (desired_vectors >= 1) {
		rc = pci_alloc_msix(ntb->device, &num_vectors);

		if (ntb_force_remap_mode != 0 && rc == 0 &&
		    num_vectors == desired_vectors)
			num_vectors--;

		if (rc == 0 && num_vectors < desired_vectors) {
			rc = intel_ntb_remap_msix(ntb->device, desired_vectors,
			    num_vectors);
			if (rc == 0)
				num_vectors = desired_vectors;
			else
				pci_release_msi(ntb->device);
		}
		if (rc != 0)
			num_vectors = 1;
	} else
		num_vectors = 1;

	if (ntb->type == NTB_XEON && num_vectors < ntb->db_vec_count) {
		if (HAS_FEATURE(ntb, NTB_SB01BASE_LOCKUP)) {
			device_printf(ntb->device,
			    "Errata workaround does not support MSI or INTX\n");
			return (EINVAL);
		}

		ntb->db_vec_count = 1;
		ntb->db_vec_shift = XEON_DB_TOTAL_SHIFT;
		rc = intel_ntb_setup_legacy_interrupt(ntb);
	} else {
		if (num_vectors - 1 != XEON_NONLINK_DB_MSIX_BITS &&
		    HAS_FEATURE(ntb, NTB_SB01BASE_LOCKUP)) {
			device_printf(ntb->device,
			    "Errata workaround expects %d doorbell bits\n",
			    XEON_NONLINK_DB_MSIX_BITS);
			return (EINVAL);
		}

		intel_ntb_create_msix_vec(ntb, num_vectors);
		rc = intel_ntb_setup_msix(ntb, num_vectors);
	}
	if (rc != 0) {
		device_printf(ntb->device,
		    "Error allocating interrupts: %d\n", rc);
		intel_ntb_free_msix_vec(ntb);
	}

	return (rc);
}