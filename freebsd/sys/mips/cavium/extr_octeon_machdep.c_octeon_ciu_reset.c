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
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_CIU_INTX_EN0 (int) ; 
 int /*<<< orphan*/  CVMX_CIU_INTX_EN1 (int) ; 
 int OCTEON_IRQ_MBOX0 ; 
 int OCTEON_IRQ_MBOX1 ; 
 int OCTEON_PMC_IRQ ; 
 int cvmx_get_core_num () ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,unsigned long long) ; 
 int mips_rd_cvmctl () ; 
 int /*<<< orphan*/  mips_wr_cvmctl (int) ; 

void
octeon_ciu_reset(void)
{
	uint64_t cvmctl;

	/* Disable all CIU interrupts by default */
	cvmx_write_csr(CVMX_CIU_INTX_EN0(cvmx_get_core_num()*2), 0);
	cvmx_write_csr(CVMX_CIU_INTX_EN0(cvmx_get_core_num()*2+1), 0);
	cvmx_write_csr(CVMX_CIU_INTX_EN1(cvmx_get_core_num()*2), 0);
	cvmx_write_csr(CVMX_CIU_INTX_EN1(cvmx_get_core_num()*2+1), 0);

#ifdef SMP
	/* Enable the MBOX interrupts.  */
	cvmx_write_csr(CVMX_CIU_INTX_EN0(cvmx_get_core_num()*2+1),
		       (1ull << (OCTEON_IRQ_MBOX0 - 8)) |
		       (1ull << (OCTEON_IRQ_MBOX1 - 8)));
#endif

	/* 
	 * Move the Performance Counter interrupt to OCTEON_PMC_IRQ
	 */
	cvmctl = mips_rd_cvmctl();
	cvmctl &= ~(7 << 7);
	cvmctl |= (OCTEON_PMC_IRQ + 2) << 7;
	mips_wr_cvmctl(cvmctl);
}