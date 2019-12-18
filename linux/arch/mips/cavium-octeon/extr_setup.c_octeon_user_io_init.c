#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int dismarkwblongto; int diswbfst; int wbthresh; int cvmsegenak; scalar_t__ cvmsegenau; scalar_t__ cvmsegenas; scalar_t__ istrnol2; scalar_t__ wbfltime; scalar_t__ mclkalwys; scalar_t__ csrckalwys; scalar_t__ didtto; scalar_t__ nomerge; scalar_t__ allsyncw; scalar_t__ xkioenau; scalar_t__ xkioenas; scalar_t__ xkmemenau; scalar_t__ xkmemenas; scalar_t__ dissyncws; scalar_t__ syncwsmarked; scalar_t__ iobdmascrmsb; scalar_t__ dismrgclrwbto; } ;
union octeon_cvmemctl {int /*<<< orphan*/  u64; TYPE_1__ s; } ;
struct TYPE_6__ {int nw_tim; } ;
union cvmx_pow_nw_tim {scalar_t__ u64; TYPE_3__ s; } ;
struct TYPE_5__ {int tout_val; scalar_t__ tout_enb; } ;
union cvmx_iob_fau_timeout {scalar_t__ u64; TYPE_2__ s; } ;

/* Variables and functions */
 int CONFIG_CAVIUM_OCTEON_CVMSEG_SIZE ; 
 int /*<<< orphan*/  CVMX_IOB_FAU_TIMEOUT ; 
 int /*<<< orphan*/  CVMX_POW_NW_TIM ; 
 int /*<<< orphan*/  OCTEON_CN38XX_PASS2 ; 
 int /*<<< orphan*/  OCTEON_CN63XX_PASS1_X ; 
 int /*<<< orphan*/  OCTEON_CN68XX ; 
 int /*<<< orphan*/  OCTEON_CN70XX ; 
 int /*<<< orphan*/  OCTEON_CN7XXX ; 
 int /*<<< orphan*/  OCTEON_FEATURE_FAU ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ octeon_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_notice (char*,int,int) ; 
 int /*<<< orphan*/  read_c0_cvmmemctl () ; 
 scalar_t__ smp_processor_id () ; 
 int /*<<< orphan*/  write_c0_cvmmemctl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_derraddr1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_octeon_c0_icacheerr (int /*<<< orphan*/ ) ; 

void octeon_user_io_init(void)
{
	union octeon_cvmemctl cvmmemctl;

	/* Get the current settings for CP0_CVMMEMCTL_REG */
	cvmmemctl.u64 = read_c0_cvmmemctl();
	/* R/W If set, marked write-buffer entries time out the same
	 * as as other entries; if clear, marked write-buffer entries
	 * use the maximum timeout. */
	cvmmemctl.s.dismarkwblongto = 1;
	/* R/W If set, a merged store does not clear the write-buffer
	 * entry timeout state. */
	cvmmemctl.s.dismrgclrwbto = 0;
	/* R/W Two bits that are the MSBs of the resultant CVMSEG LM
	 * word location for an IOBDMA. The other 8 bits come from the
	 * SCRADDR field of the IOBDMA. */
	cvmmemctl.s.iobdmascrmsb = 0;
	/* R/W If set, SYNCWS and SYNCS only order marked stores; if
	 * clear, SYNCWS and SYNCS only order unmarked
	 * stores. SYNCWSMARKED has no effect when DISSYNCWS is
	 * set. */
	cvmmemctl.s.syncwsmarked = 0;
	/* R/W If set, SYNCWS acts as SYNCW and SYNCS acts as SYNC. */
	cvmmemctl.s.dissyncws = 0;
	/* R/W If set, no stall happens on write buffer full. */
	if (OCTEON_IS_MODEL(OCTEON_CN38XX_PASS2))
		cvmmemctl.s.diswbfst = 1;
	else
		cvmmemctl.s.diswbfst = 0;
	/* R/W If set (and SX set), supervisor-level loads/stores can
	 * use XKPHYS addresses with <48>==0 */
	cvmmemctl.s.xkmemenas = 0;

	/* R/W If set (and UX set), user-level loads/stores can use
	 * XKPHYS addresses with VA<48>==0 */
	cvmmemctl.s.xkmemenau = 0;

	/* R/W If set (and SX set), supervisor-level loads/stores can
	 * use XKPHYS addresses with VA<48>==1 */
	cvmmemctl.s.xkioenas = 0;

	/* R/W If set (and UX set), user-level loads/stores can use
	 * XKPHYS addresses with VA<48>==1 */
	cvmmemctl.s.xkioenau = 0;

	/* R/W If set, all stores act as SYNCW (NOMERGE must be set
	 * when this is set) RW, reset to 0. */
	cvmmemctl.s.allsyncw = 0;

	/* R/W If set, no stores merge, and all stores reach the
	 * coherent bus in order. */
	cvmmemctl.s.nomerge = 0;
	/* R/W Selects the bit in the counter used for DID time-outs 0
	 * = 231, 1 = 230, 2 = 229, 3 = 214. Actual time-out is
	 * between 1x and 2x this interval. For example, with
	 * DIDTTO=3, expiration interval is between 16K and 32K. */
	cvmmemctl.s.didtto = 0;
	/* R/W If set, the (mem) CSR clock never turns off. */
	cvmmemctl.s.csrckalwys = 0;
	/* R/W If set, mclk never turns off. */
	cvmmemctl.s.mclkalwys = 0;
	/* R/W Selects the bit in the counter used for write buffer
	 * flush time-outs (WBFLT+11) is the bit position in an
	 * internal counter used to determine expiration. The write
	 * buffer expires between 1x and 2x this interval. For
	 * example, with WBFLT = 0, a write buffer expires between 2K
	 * and 4K cycles after the write buffer entry is allocated. */
	cvmmemctl.s.wbfltime = 0;
	/* R/W If set, do not put Istream in the L2 cache. */
	cvmmemctl.s.istrnol2 = 0;

	/*
	 * R/W The write buffer threshold. As per erratum Core-14752
	 * for CN63XX, a sc/scd might fail if the write buffer is
	 * full.  Lowering WBTHRESH greatly lowers the chances of the
	 * write buffer ever being full and triggering the erratum.
	 */
	if (OCTEON_IS_MODEL(OCTEON_CN63XX_PASS1_X))
		cvmmemctl.s.wbthresh = 4;
	else
		cvmmemctl.s.wbthresh = 10;

	/* R/W If set, CVMSEG is available for loads/stores in
	 * kernel/debug mode. */
#if CONFIG_CAVIUM_OCTEON_CVMSEG_SIZE > 0
	cvmmemctl.s.cvmsegenak = 1;
#else
	cvmmemctl.s.cvmsegenak = 0;
#endif
	/* R/W If set, CVMSEG is available for loads/stores in
	 * supervisor mode. */
	cvmmemctl.s.cvmsegenas = 0;
	/* R/W If set, CVMSEG is available for loads/stores in user
	 * mode. */
	cvmmemctl.s.cvmsegenau = 0;

	write_c0_cvmmemctl(cvmmemctl.u64);

	/* Setup of CVMSEG is done in kernel-entry-init.h */
	if (smp_processor_id() == 0)
		pr_notice("CVMSEG size: %d cache lines (%d bytes)\n",
			  CONFIG_CAVIUM_OCTEON_CVMSEG_SIZE,
			  CONFIG_CAVIUM_OCTEON_CVMSEG_SIZE * 128);

	if (octeon_has_feature(OCTEON_FEATURE_FAU)) {
		union cvmx_iob_fau_timeout fau_timeout;

		/* Set a default for the hardware timeouts */
		fau_timeout.u64 = 0;
		fau_timeout.s.tout_val = 0xfff;
		/* Disable tagwait FAU timeout */
		fau_timeout.s.tout_enb = 0;
		cvmx_write_csr(CVMX_IOB_FAU_TIMEOUT, fau_timeout.u64);
	}

	if ((!OCTEON_IS_MODEL(OCTEON_CN68XX) &&
	     !OCTEON_IS_MODEL(OCTEON_CN7XXX)) ||
	    OCTEON_IS_MODEL(OCTEON_CN70XX)) {
		union cvmx_pow_nw_tim nm_tim;

		nm_tim.u64 = 0;
		/* 4096 cycles */
		nm_tim.s.nw_tim = 3;
		cvmx_write_csr(CVMX_POW_NW_TIM, nm_tim.u64);
	}

	write_octeon_c0_icacheerr(0);
	write_c0_derraddr1(0);
}