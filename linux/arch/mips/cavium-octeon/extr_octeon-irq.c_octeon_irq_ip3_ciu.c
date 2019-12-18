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
 int /*<<< orphan*/  CVMX_CIU_INT_SUM1 ; 
 int __this_cpu_read (int /*<<< orphan*/ ) ; 
 int cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_IRQ (int) ; 
 int fls64 (int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  octeon_irq_ciu1_en_mirror ; 
 int** octeon_irq_ciu_to_irq ; 
 int /*<<< orphan*/  spurious_interrupt () ; 

__attribute__((used)) static void octeon_irq_ip3_ciu(void)
{
	u64 ciu_sum = cvmx_read_csr(CVMX_CIU_INT_SUM1);

	ciu_sum &= __this_cpu_read(octeon_irq_ciu1_en_mirror);
	if (likely(ciu_sum)) {
		int bit = fls64(ciu_sum) - 1;
		int irq = octeon_irq_ciu_to_irq[1][bit];
		if (likely(irq))
			do_IRQ(irq);
		else
			spurious_interrupt();
	} else {
		spurious_interrupt();
	}
}