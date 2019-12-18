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
struct ena_intr_moder_entry {unsigned int pkts_per_interval; unsigned int bytes_per_interval; unsigned int intr_moder_interval; } ;
struct ena_com_dev {struct ena_intr_moder_entry* intr_moder_tbl; } ;
typedef  enum ena_intr_moder_level { ____Placeholder_ena_intr_moder_level } ena_intr_moder_level ;

/* Variables and functions */
 unsigned int ENA_INTR_DELAY_NEW_VALUE_WEIGHT ; 
 unsigned int ENA_INTR_DELAY_OLD_VALUE_WEIGHT ; 
 int ENA_INTR_MAX_NUM_OF_LEVELS ; 
 int ENA_INTR_MODER_HIGHEST ; 
 int ENA_INTR_MODER_LEVEL_STRIDE ; 
 int ENA_INTR_MODER_LOWEST ; 
 int /*<<< orphan*/  ena_trc_err (char*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void ena_com_calculate_interrupt_delay(struct ena_com_dev *ena_dev,
						     unsigned int pkts,
						     unsigned int bytes,
						     unsigned int *smoothed_interval,
						     unsigned int *moder_tbl_idx)
{
	enum ena_intr_moder_level curr_moder_idx, new_moder_idx;
	struct ena_intr_moder_entry *curr_moder_entry;
	struct ena_intr_moder_entry *pred_moder_entry;
	struct ena_intr_moder_entry *new_moder_entry;
	struct ena_intr_moder_entry *intr_moder_tbl = ena_dev->intr_moder_tbl;
	unsigned int interval;

	/* We apply adaptive moderation on Rx path only.
	 * Tx uses static interrupt moderation.
	 */
	if (!pkts || !bytes)
		/* Tx interrupt, or spurious interrupt,
		 * in both cases we just use same delay values
		 */
		return;

	curr_moder_idx = (enum ena_intr_moder_level)(*moder_tbl_idx);
	if (unlikely(curr_moder_idx >=  ENA_INTR_MAX_NUM_OF_LEVELS)) {
		ena_trc_err("Wrong moderation index %u\n", curr_moder_idx);
		return;
	}

	curr_moder_entry = &intr_moder_tbl[curr_moder_idx];
	new_moder_idx = curr_moder_idx;

	if (curr_moder_idx == ENA_INTR_MODER_LOWEST) {
		if ((pkts > curr_moder_entry->pkts_per_interval) ||
		    (bytes > curr_moder_entry->bytes_per_interval))
			new_moder_idx =
				(enum ena_intr_moder_level)(curr_moder_idx + ENA_INTR_MODER_LEVEL_STRIDE);
	} else {
		pred_moder_entry = &intr_moder_tbl[curr_moder_idx - ENA_INTR_MODER_LEVEL_STRIDE];

		if ((pkts <= pred_moder_entry->pkts_per_interval) ||
		    (bytes <= pred_moder_entry->bytes_per_interval))
			new_moder_idx =
				(enum ena_intr_moder_level)(curr_moder_idx - ENA_INTR_MODER_LEVEL_STRIDE);
		else if ((pkts > curr_moder_entry->pkts_per_interval) ||
			 (bytes > curr_moder_entry->bytes_per_interval)) {
			if (curr_moder_idx != ENA_INTR_MODER_HIGHEST)
				new_moder_idx =
					(enum ena_intr_moder_level)(curr_moder_idx + ENA_INTR_MODER_LEVEL_STRIDE);
		}
	}
	new_moder_entry = &intr_moder_tbl[new_moder_idx];

	interval = new_moder_entry->intr_moder_interval;
	*smoothed_interval = (
		(interval * ENA_INTR_DELAY_NEW_VALUE_WEIGHT +
		ENA_INTR_DELAY_OLD_VALUE_WEIGHT * (*smoothed_interval)) + 5) /
		10;

	*moder_tbl_idx = new_moder_idx;
}