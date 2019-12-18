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
struct TYPE_2__ {int calerr; int syncerr; int diperr; int tpaovr; int rsverr; int drwnng; int clserr; int spiovr; int abnorm; int prtnxa; } ;
union cvmx_spxx_int_msk {scalar_t__ u64; TYPE_1__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_SPXX_INT_MSK (int) ; 
 int /*<<< orphan*/  CVMX_SPXX_INT_REG (int) ; 
 int /*<<< orphan*/  OCTEON_CN38XX ; 
 int /*<<< orphan*/  OCTEON_CN58XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 scalar_t__ cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,scalar_t__) ; 

void __cvmx_interrupt_spxx_int_msk_enable(int index)
{
	union cvmx_spxx_int_msk spx_int_msk;
	cvmx_write_csr(CVMX_SPXX_INT_REG(index),
		       cvmx_read_csr(CVMX_SPXX_INT_REG(index)));
	spx_int_msk.u64 = 0;
	if (OCTEON_IS_MODEL(OCTEON_CN38XX)) {
		/* Skipping spx_int_msk.s.reserved_12_63 */
		spx_int_msk.s.calerr = 1;
		spx_int_msk.s.syncerr = 1;
		spx_int_msk.s.diperr = 1;
		spx_int_msk.s.tpaovr = 1;
		spx_int_msk.s.rsverr = 1;
		spx_int_msk.s.drwnng = 1;
		spx_int_msk.s.clserr = 1;
		spx_int_msk.s.spiovr = 1;
		/* Skipping spx_int_msk.s.reserved_2_3 */
		spx_int_msk.s.abnorm = 1;
		spx_int_msk.s.prtnxa = 1;
	}
	if (OCTEON_IS_MODEL(OCTEON_CN58XX)) {
		/* Skipping spx_int_msk.s.reserved_12_63 */
		spx_int_msk.s.calerr = 1;
		spx_int_msk.s.syncerr = 1;
		spx_int_msk.s.diperr = 1;
		spx_int_msk.s.tpaovr = 1;
		spx_int_msk.s.rsverr = 1;
		spx_int_msk.s.drwnng = 1;
		spx_int_msk.s.clserr = 1;
		spx_int_msk.s.spiovr = 1;
		/* Skipping spx_int_msk.s.reserved_2_3 */
		spx_int_msk.s.abnorm = 1;
		spx_int_msk.s.prtnxa = 1;
	}
	cvmx_write_csr(CVMX_SPXX_INT_MSK(index), spx_int_msk.u64);
}