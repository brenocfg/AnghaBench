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
struct TYPE_2__ {int txpsh; int txpop; int ovrflw; } ;
union cvmx_asxx_int_en {int /*<<< orphan*/  u64; TYPE_1__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_ASXX_INT_EN (int) ; 
 int /*<<< orphan*/  OCTEON_CN38XX ; 
 int /*<<< orphan*/  OCTEON_CN58XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void __cvmx_interrupt_asxx_enable(int block)
{
	int mask;
	union cvmx_asxx_int_en csr;
	/*
	 * CN38XX and CN58XX have two interfaces with 4 ports per
	 * interface. All other chips have a max of 3 ports on
	 * interface 0
	 */
	if (OCTEON_IS_MODEL(OCTEON_CN38XX) || OCTEON_IS_MODEL(OCTEON_CN58XX))
		mask = 0xf;	/* Set enables for 4 ports */
	else
		mask = 0x7;	/* Set enables for 3 ports */

	/* Enable interface interrupts */
	csr.u64 = cvmx_read_csr(CVMX_ASXX_INT_EN(block));
	csr.s.txpsh = mask;
	csr.s.txpop = mask;
	csr.s.ovrflw = mask;
	cvmx_write_csr(CVMX_ASXX_INT_EN(block), csr.u64);
}