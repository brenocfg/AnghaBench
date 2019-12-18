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
struct adf_etr_ring_data {int /*<<< orphan*/  ring_number; struct adf_etr_bank_data* bank; } ;
struct adf_etr_bank_data {int /*<<< orphan*/  bank_number; int /*<<< orphan*/  csr_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_CSR_RING_BASE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_CSR_RING_CONFIG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adf_cleanup_ring (struct adf_etr_ring_data*) ; 
 int /*<<< orphan*/  adf_disable_ring_irq (struct adf_etr_bank_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adf_ring_debugfs_rm (struct adf_etr_ring_data*) ; 
 int /*<<< orphan*/  adf_unreserve_ring (struct adf_etr_bank_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adf_update_ring_arb (struct adf_etr_ring_data*) ; 

void adf_remove_ring(struct adf_etr_ring_data *ring)
{
	struct adf_etr_bank_data *bank = ring->bank;

	/* Disable interrupts for the given ring */
	adf_disable_ring_irq(bank, ring->ring_number);

	/* Clear PCI config space */
	WRITE_CSR_RING_CONFIG(bank->csr_addr, bank->bank_number,
			      ring->ring_number, 0);
	WRITE_CSR_RING_BASE(bank->csr_addr, bank->bank_number,
			    ring->ring_number, 0);
	adf_ring_debugfs_rm(ring);
	adf_unreserve_ring(bank, ring->ring_number);
	/* Disable HW arbitration for the given ring */
	adf_update_ring_arb(ring);
	adf_cleanup_ring(ring);
}