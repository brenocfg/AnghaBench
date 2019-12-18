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
typedef  int u64 ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_CIU2_ACK_PPX_IP3 (unsigned long const) ; 
 int /*<<< orphan*/  CVMX_CIU2_INTR_CIU_READY ; 
 int /*<<< orphan*/  CVMX_CIU2_SUM_PPX_IP3 (unsigned long const) ; 
 int /*<<< orphan*/  OCTEON_CN68XX ; 
 scalar_t__ OCTEON_IRQ_MBOX0 ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 unsigned long cvmx_get_core_num () ; 
 int cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_IRQ (scalar_t__) ; 
 int fls64 (int) ; 
 int /*<<< orphan*/  spurious_interrupt () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void octeon_irq_ciu2_mbox(void)
{
	int line;

	const unsigned long core_id = cvmx_get_core_num();
	u64 sum = cvmx_read_csr(CVMX_CIU2_SUM_PPX_IP3(core_id)) >> 60;

	if (unlikely(!sum))
		goto spurious;

	line = fls64(sum) - 1;

	do_IRQ(OCTEON_IRQ_MBOX0 + line);
	goto out;

spurious:
	spurious_interrupt();
out:
	/* CN68XX pass 1.x has an errata that accessing the ACK registers
		can stop interrupts from propagating */
	if (OCTEON_IS_MODEL(OCTEON_CN68XX))
		cvmx_read_csr(CVMX_CIU2_INTR_CIU_READY);
	else
		cvmx_read_csr(CVMX_CIU2_ACK_PPX_IP3(core_id));
	return;
}