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

/* Variables and functions */
 int /*<<< orphan*/  CVMX_CIU_INTX_EN0 (int) ; 
 int /*<<< orphan*/  CVMX_CIU_INTX_EN1 (int) ; 
 int /*<<< orphan*/  CVMX_CIU_INTX_SUM0 (int) ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cvmx_get_core_num () ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_irq_ciu0_en_mirror ; 
 int /*<<< orphan*/  octeon_irq_ciu1_en_mirror ; 
 int /*<<< orphan*/  octeon_irq_ciu_spinlock ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void octeon_irq_init_ciu_percpu(void)
{
	int coreid = cvmx_get_core_num();


	__this_cpu_write(octeon_irq_ciu0_en_mirror, 0);
	__this_cpu_write(octeon_irq_ciu1_en_mirror, 0);
	wmb();
	raw_spin_lock_init(this_cpu_ptr(&octeon_irq_ciu_spinlock));
	/*
	 * Disable All CIU Interrupts. The ones we need will be
	 * enabled later.  Read the SUM register so we know the write
	 * completed.
	 */
	cvmx_write_csr(CVMX_CIU_INTX_EN0((coreid * 2)), 0);
	cvmx_write_csr(CVMX_CIU_INTX_EN0((coreid * 2 + 1)), 0);
	cvmx_write_csr(CVMX_CIU_INTX_EN1((coreid * 2)), 0);
	cvmx_write_csr(CVMX_CIU_INTX_EN1((coreid * 2 + 1)), 0);
	cvmx_read_csr(CVMX_CIU_INTX_SUM0((coreid * 2)));
}