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
typedef  unsigned int uint32_t ;
struct pt_time_cal {unsigned int ctc; unsigned int have_mtc; unsigned long long cyc_mtc; unsigned int check_skl168; unsigned long long fcr; scalar_t__ lost_mtc; } ;
struct pt_packet_mtc {scalar_t__ ctc; } ;
struct pt_config {unsigned int mtc_freq; } ;

/* Variables and functions */
 unsigned long long pt_tcal_fcr_shr ; 
 scalar_t__ pt_tcal_have_fcr (struct pt_time_cal*) ; 
 int pt_tcal_set_fcr (struct pt_time_cal*,unsigned long long) ; 
 int pt_time_ctc_delta (unsigned int*,unsigned int,unsigned int,struct pt_config const*) ; 
 int pt_time_ctc_fc (unsigned long long*,unsigned int,struct pt_config const*) ; 
 int pte_internal ; 

int pt_tcal_update_mtc(struct pt_time_cal *tcal,
		      const struct pt_packet_mtc *packet,
		      const struct pt_config *config)
{
	uint32_t last_ctc, ctc, ctc_delta, have_mtc, check_skl168;
	uint64_t cyc, fc, fcr;
	int errcode;

	if (!tcal || !packet || !config)
		return -pte_internal;

	last_ctc = tcal->ctc;
	have_mtc = tcal->have_mtc;
	cyc = tcal->cyc_mtc;
	check_skl168 = tcal->check_skl168;

	/* This only affects the first MTC after PSB. */
	tcal->check_skl168 = 0;

	ctc = (uint32_t) packet->ctc << config->mtc_freq;

	/* We need at least two MTC (including this). */
	if (!have_mtc) {
		tcal->cyc_mtc = 0ull;
		tcal->ctc = ctc;
		tcal->have_mtc = 1;

		return 0;
	}

	/* Without any cycles, we can't calibrate.  Try again at the next
	 * MTC and distribute the cycles over the combined MTC period.
	 */
	if (!cyc)
		return 0;

	/* Prepare for the next packet in case we error out below. */
	tcal->have_mtc = 1;
	tcal->cyc_mtc = 0ull;
	tcal->ctc = ctc;

	/* Let's pretend we will fail.  We'll correct it at the end. */
	tcal->lost_mtc += 1;

	errcode = pt_time_ctc_delta(&ctc_delta, ctc, last_ctc, config);
	if (errcode < 0)
		return errcode;

	errcode = pt_time_ctc_fc(&fc, ctc_delta, config);
	if (errcode < 0)
		return errcode;

	/* We shift the nominator to improve rounding precision.
	 *
	 * Since we're only collecting the CYCs between two MTC, we shouldn't
	 * overflow.  Let's rather fail than overflow.
	 */
	if (fc & ~(~0ull >> pt_tcal_fcr_shr))
		return -pte_internal;

	fcr = (fc << pt_tcal_fcr_shr) / cyc;

	/* SKL168: Intel(R) PT CYC Packets Can be Dropped When Immediately
	 * Preceding PSB.
	 *
	 * We skip this MTC if we lost one or more MTC since the last PSB or if
	 * it looks like we lost a wrap CYC packet.
	 *
	 * This is not an error but we count that MTC as lost.
	 */
	if (check_skl168) {
		/* If we lost one or more MTC, the case is clear. */
		if ((1u << config->mtc_freq) < ctc_delta)
			return 0;

		/* The case is less clear for a lost wrap CYC packet since we do
		 * have some variation in the number of cycles.
		 *
		 * The CYC counter wraps on the affected processors every 4096
		 * cycles.  For low MTC frequencies (high values), losing one
		 * may not be noticeable.
		 *
		 * We restrict the workaround to higher MTC frequencies (lower
		 * values).
		 *
		 * We also need a previous FCR so we know how many cycles to
		 * expect.
		 */
		if ((config->mtc_freq < 10) && pt_tcal_have_fcr(tcal)) {
			uint64_t dfc;

			/* We choose a slightly lower adjustment to account for
			 * some normal variation.
			 */
			dfc = (tcal->fcr * (cyc + 0xf00)) >> pt_tcal_fcr_shr;

			/* If we didn't drop a wrap CYC, @dfc should be way
			 * bigger than @fc.  If it isn't, we assume that the
			 * erratum applied.
			 */
			if (dfc < fc)
				return 0;
		}
	}

	errcode = pt_tcal_set_fcr(tcal, fcr);
	if (errcode < 0)
		return errcode;

	/* We updated the FCR.  This recovers from previous MTC losses. */
	tcal->lost_mtc = 0;

	return 0;
}