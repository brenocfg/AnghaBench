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
typedef  scalar_t__ uint64_t ;
typedef  unsigned int uint32_t ;
struct pt_time {int have_tma; int have_mtc; unsigned int ctc; unsigned int ctc_cyc; int /*<<< orphan*/  fc; int /*<<< orphan*/  base; int /*<<< orphan*/  have_tsc; } ;
struct pt_packet_tma {unsigned int ctc; scalar_t__ fc; } ;
struct pt_config {unsigned int mtc_freq; } ;

/* Variables and functions */
 unsigned int pt_pl_mtc_bit_size ; 
 unsigned int pt_pl_tma_ctc_bit_size ; 
 int pte_bad_context ; 
 int pte_internal ; 

int pt_time_update_tma(struct pt_time *time,
		       const struct pt_packet_tma *packet,
		       const struct pt_config *config)
{
	uint32_t ctc, mtc_freq, mtc_hi, ctc_mask;
	uint64_t fc;

	if (!time || !packet || !config)
		return -pte_internal;

	/* Without a TSC something is seriously wrong. */
	if (!time->have_tsc)
		return -pte_bad_context;

	/* We shouldn't have more than one TMA per TSC. */
	if (time->have_tma)
		return -pte_bad_context;

	/* We're ignoring MTC between TSC and TMA. */
	if (time->have_mtc)
		return -pte_internal;

	ctc = packet->ctc;
	fc = packet->fc;

	mtc_freq = config->mtc_freq;
	mtc_hi = mtc_freq + pt_pl_mtc_bit_size;

	/* A mask for the relevant CTC bits ignoring high-order bits that are
	 * not provided by MTC.
	 */
	ctc_mask = (1u << mtc_hi) - 1u;

	time->have_tma = 1;
	time->base -= fc;
	time->fc += fc;

	/* If the MTC frequency is low enough that TMA provides the full CTC
	 * value, we can use the TMA as an MTC.
	 *
	 * If it isn't, we will estimate the preceding MTC based on the CTC bits
	 * the TMA provides at the next MTC.  We forget about the previous MTC
	 * in this case.
	 *
	 * If no MTC packets are dropped around TMA, we will estimate the
	 * forgotten value again at the next MTC.
	 *
	 * If MTC packets are dropped, we can't really tell where in this
	 * extended MTC period the TSC occurred.  The estimation will place it
	 * right before the next MTC.
	 */
	if (mtc_hi <= pt_pl_tma_ctc_bit_size)
		time->have_mtc = 1;

	/* In both cases, we store the TMA's CTC bits until the next MTC. */
	time->ctc = time->ctc_cyc = ctc & ctc_mask;

	return 0;
}