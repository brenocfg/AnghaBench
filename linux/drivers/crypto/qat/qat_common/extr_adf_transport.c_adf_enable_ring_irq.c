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
typedef  int uint32_t ;
struct adf_etr_bank_data {int irq_mask; int /*<<< orphan*/  irq_coalesc_timer; int /*<<< orphan*/  bank_number; int /*<<< orphan*/  csr_addr; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_CSR_INT_COL_CTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_CSR_INT_COL_EN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void adf_enable_ring_irq(struct adf_etr_bank_data *bank, uint32_t ring)
{
	spin_lock_bh(&bank->lock);
	bank->irq_mask |= (1 << ring);
	spin_unlock_bh(&bank->lock);
	WRITE_CSR_INT_COL_EN(bank->csr_addr, bank->bank_number, bank->irq_mask);
	WRITE_CSR_INT_COL_CTL(bank->csr_addr, bank->bank_number,
			      bank->irq_coalesc_timer);
}