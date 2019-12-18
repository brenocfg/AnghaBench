#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int size1; int size2; int size3; int size4; int size5; int size6; int size7; } ;
union cvmx_pko_reg_min_pkt {scalar_t__ u64; TYPE_2__ s; } ;
struct TYPE_3__ {int tout_val; scalar_t__ tout_enb; } ;
union cvmx_iob_fau_timeout {scalar_t__ u64; TYPE_1__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_IOB_FAU_TIMEOUT ; 
 int /*<<< orphan*/  CVMX_PKO_REG_MIN_PKT ; 
 int /*<<< orphan*/  OCTEON_CN68XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int __cvmx_helper_global_setup_pko(void)
{
	/*
	 * Disable tagwait FAU timeout. This needs to be done before
	 * anyone might start packet output using tags.
	 */
	union cvmx_iob_fau_timeout fau_to;
	fau_to.u64 = 0;
	fau_to.s.tout_val = 0xfff;
	fau_to.s.tout_enb = 0;
	cvmx_write_csr(CVMX_IOB_FAU_TIMEOUT, fau_to.u64);

	if (OCTEON_IS_MODEL(OCTEON_CN68XX)) {
		union cvmx_pko_reg_min_pkt min_pkt;

		min_pkt.u64 = 0;
		min_pkt.s.size1 = 59;
		min_pkt.s.size2 = 59;
		min_pkt.s.size3 = 59;
		min_pkt.s.size4 = 59;
		min_pkt.s.size5 = 59;
		min_pkt.s.size6 = 59;
		min_pkt.s.size7 = 59;
		cvmx_write_csr(CVMX_PKO_REG_MIN_PKT, min_pkt.u64);
	}

	return 0;
}