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

/* Variables and functions */
 unsigned int N_BIN_SHARDS_DEFAULT ; 
 unsigned int SC_NBINS ; 

void
bin_shard_sizes_boot(unsigned bin_shard_sizes[SC_NBINS]) {
	/* Load the default number of shards. */
	for (unsigned i = 0; i < SC_NBINS; i++) {
		bin_shard_sizes[i] = N_BIN_SHARDS_DEFAULT;
	}
}