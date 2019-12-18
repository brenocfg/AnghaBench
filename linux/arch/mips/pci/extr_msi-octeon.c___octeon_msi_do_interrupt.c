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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int OCTEON_IRQ_MSI_BIT0 ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  do_IRQ (int) ; 
 int fls64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * msi_rcv_reg ; 

__attribute__((used)) static irqreturn_t __octeon_msi_do_interrupt(int index, u64 msi_bits)
{
	int irq;
	int bit;

	bit = fls64(msi_bits);
	if (bit) {
		bit--;
		/* Acknowledge it first. */
		cvmx_write_csr(msi_rcv_reg[index], 1ull << bit);

		irq = bit + OCTEON_IRQ_MSI_BIT0 + 64 * index;
		do_IRQ(irq);
		return IRQ_HANDLED;
	}
	return IRQ_NONE;
}