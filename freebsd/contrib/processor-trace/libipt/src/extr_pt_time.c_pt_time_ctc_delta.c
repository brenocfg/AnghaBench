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
typedef  scalar_t__ uint32_t ;
struct pt_config {unsigned int mtc_freq; } ;

/* Variables and functions */
 unsigned int pt_pl_mtc_bit_size ; 
 int pte_bad_packet ; 
 int pte_internal ; 

__attribute__((used)) static int pt_time_ctc_delta(uint32_t *ctc_delta, uint32_t ctc,
			     uint32_t last_ctc, const struct pt_config *config)
{
	if (!config || !ctc_delta)
		return -pte_internal;

	/* Correct a single wrap-around.  If we lost enough MTCs to wrap
	 * around twice, timing will be wrong until the next TSC.
	 */
	if (ctc < last_ctc) {
		ctc += 1u << (config->mtc_freq + pt_pl_mtc_bit_size);

		/* Since we only store the CTC between TMA/MTC or MTC/TMC a
		 * single correction should suffice.
		 */
		if (ctc < last_ctc)
			return -pte_bad_packet;
	}

	*ctc_delta = ctc - last_ctc;
	return 0;
}