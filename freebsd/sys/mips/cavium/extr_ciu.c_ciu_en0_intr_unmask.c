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
typedef  unsigned long long uint64_t ;

/* Variables and functions */
 int CIU_IRQ_EN0_BEGIN ; 
 int /*<<< orphan*/  CVMX_CIU_INTX_EN0 (int) ; 
 int cvmx_get_core_num () ; 
 unsigned long long cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static void
ciu_en0_intr_unmask(void *arg)
{
	uint64_t mask;
	int irq;

	irq = (uintptr_t)arg;
	mask = cvmx_read_csr(CVMX_CIU_INTX_EN0(cvmx_get_core_num()*2));
	mask |= 1ull << (irq - CIU_IRQ_EN0_BEGIN);
	cvmx_write_csr(CVMX_CIU_INTX_EN0(cvmx_get_core_num()*2), mask);
}