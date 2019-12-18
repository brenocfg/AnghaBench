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
typedef  int uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct pt_time {int have_tsc; int have_tma; int have_mtc; int ctc; unsigned long long fc; int ctc_cyc; int lost_mtc; scalar_t__ base; scalar_t__ tsc; scalar_t__ lost_cyc; } ;
struct pt_packet_mtc {scalar_t__ ctc; } ;
struct pt_config {int mtc_freq; } ;

/* Variables and functions */
 scalar_t__ pt_pl_mtc_mask ; 
 unsigned int pt_pl_tma_ctc_bit_size ; 
 scalar_t__ pt_pl_tma_ctc_mask ; 
 int pt_time_ctc_delta (int*,int,int,struct pt_config const*) ; 
 int pt_time_ctc_fc (scalar_t__*,int,struct pt_config const*) ; 
 int pte_internal ; 

int pt_time_update_mtc(struct pt_time *time,
		       const struct pt_packet_mtc *packet,
		       const struct pt_config *config)
{
	uint32_t last_ctc, ctc, ctc_delta;
	uint64_t tsc, base;
	uint8_t mtc_freq;
	int errcode, have_tsc, have_tma, have_mtc;

	if (!time || !packet || !config)
		return -pte_internal;

	have_tsc = time->have_tsc;
	have_tma = time->have_tma;
	have_mtc = time->have_mtc;

	/* We ignore MTCs between TSC and TMA to avoid apparent CTC overflows.
	 *
	 * Later MTCs will ensure that no time is lost - provided TMA provides
	 * enough bits.  If TMA doesn't provide any of the MTC bits we may place
	 * the TSC into the wrong MTC period.
	 */
	if (have_tsc && !have_tma)
		return 0;

	base = time->base;
	last_ctc = time->ctc;
	mtc_freq = config->mtc_freq;

	ctc = (uint32_t) packet->ctc << mtc_freq;

	/* Store our CTC value if we have or would have reset FC. */
	if (time->fc || time->lost_cyc || !have_mtc)
		time->ctc_cyc = ctc;

	/* Prepare for the next packet in case we error out below. */
	time->have_mtc = 1;
	time->fc = 0ull;
	time->ctc = ctc;

	/* We recover from previous CYC losses. */
	time->lost_cyc = 0;

	/* Avoid a big jump when we see the first MTC with an arbitrary CTC
	 * payload.
	 */
	if (!have_mtc) {
		uint32_t ctc_lo, ctc_hi;

		/* If we have not seen a TMA, we ignore this first MTC.
		 *
		 * We have no idea where in this MTC period tracing started.
		 * We could lose an entire MTC period or just a tiny fraction.
		 *
		 * On the other hand, if we assumed a previous MTC value, we
		 * might make just the same error.
		 */
		if (!have_tma)
			return 0;

		/* The TMA's CTC value didn't provide enough bits - otherwise,
		 * we would have treated the TMA as an MTC.
		 */
		if (last_ctc & ~(uint32_t) pt_pl_tma_ctc_mask)
			return -pte_internal;

		/* Split this MTC's CTC value into low and high parts with
		 * respect to the bits provided by TMA.
		 */
		ctc_lo = ctc & (uint32_t) pt_pl_tma_ctc_mask;
		ctc_hi = ctc & ~(uint32_t) pt_pl_tma_ctc_mask;

		/* We estimate the high-order CTC bits that are not provided by
		 * TMA based on the CTC bits provided by this MTC.
		 *
		 * We assume that no MTC packets were dropped around TMA.  If
		 * there are, we might place the TSC into the wrong MTC period
		 * depending on how many CTC bits TMA provides and how many MTC
		 * packets were dropped.
		 *
		 * Note that we may underflow which results in more bits to be
		 * set than MTC packets may provide.  Drop those extra bits.
		 */
		if (ctc_lo < last_ctc) {
			ctc_hi -= 1u << pt_pl_tma_ctc_bit_size;
			ctc_hi &= (uint32_t) pt_pl_mtc_mask << mtc_freq;
		}

		last_ctc |= ctc_hi;
	}

	errcode = pt_time_ctc_delta(&ctc_delta, ctc, last_ctc, config);
	if (errcode < 0) {
		time->lost_mtc += 1;
		return errcode;
	}

	errcode = pt_time_ctc_fc(&tsc, ctc_delta, config);
	if (errcode < 0)
		return errcode;

	base += tsc;
	time->tsc = time->base = base;

	return 0;
}