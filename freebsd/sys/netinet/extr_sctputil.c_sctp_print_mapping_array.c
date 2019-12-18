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
struct sctp_association {unsigned int mapping_array_size; scalar_t__* mapping_array; scalar_t__* nr_mapping_array; int /*<<< orphan*/  highest_tsn_inside_nr_map; int /*<<< orphan*/  highest_tsn_inside_map; int /*<<< orphan*/  cumulative_tsn; int /*<<< orphan*/  mapping_array_base_tsn; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_PRINTF (char*,...) ; 

void
sctp_print_mapping_array(struct sctp_association *asoc)
{
	unsigned int i, limit;

	SCTP_PRINTF("Mapping array size: %d, baseTSN: %8.8x, cumAck: %8.8x, highestTSN: (%8.8x, %8.8x).\n",
	    asoc->mapping_array_size,
	    asoc->mapping_array_base_tsn,
	    asoc->cumulative_tsn,
	    asoc->highest_tsn_inside_map,
	    asoc->highest_tsn_inside_nr_map);
	for (limit = asoc->mapping_array_size; limit > 1; limit--) {
		if (asoc->mapping_array[limit - 1] != 0) {
			break;
		}
	}
	SCTP_PRINTF("Renegable mapping array (last %d entries are zero):\n", asoc->mapping_array_size - limit);
	for (i = 0; i < limit; i++) {
		SCTP_PRINTF("%2.2x%c", asoc->mapping_array[i], ((i + 1) % 16) ? ' ' : '\n');
	}
	if (limit % 16)
		SCTP_PRINTF("\n");
	for (limit = asoc->mapping_array_size; limit > 1; limit--) {
		if (asoc->nr_mapping_array[limit - 1]) {
			break;
		}
	}
	SCTP_PRINTF("Non renegable mapping array (last %d entries are zero):\n", asoc->mapping_array_size - limit);
	for (i = 0; i < limit; i++) {
		SCTP_PRINTF("%2.2x%c", asoc->nr_mapping_array[i], ((i + 1) % 16) ? ' ' : '\n');
	}
	if (limit % 16)
		SCTP_PRINTF("\n");
}