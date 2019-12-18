#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_3__ {size_t** dist_slot_prices; size_t dist_table_size; size_t** dist_prices; size_t const dist_special; scalar_t__ match_price_count; int /*<<< orphan*/ * dist_slot; } ;
typedef  TYPE_1__ lzma_lzma1_encoder ;

/* Variables and functions */
 size_t ALIGN_BITS ; 
 size_t DIST_MODEL_END ; 
 size_t DIST_MODEL_START ; 
 int /*<<< orphan*/  DIST_SLOT_BITS ; 
 size_t DIST_STATES ; 
 size_t FULL_DISTANCES ; 
 size_t get_dist_slot (size_t) ; 
 size_t rc_bittree_price (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 size_t rc_bittree_reverse_price (size_t const,size_t const,size_t) ; 
 scalar_t__ rc_direct_price (size_t) ; 

__attribute__((used)) static void
fill_dist_prices(lzma_lzma1_encoder *coder)
{
	for (uint32_t dist_state = 0; dist_state < DIST_STATES; ++dist_state) {

		uint32_t *const dist_slot_prices
				= coder->dist_slot_prices[dist_state];

		// Price to encode the dist_slot.
		for (uint32_t dist_slot = 0;
				dist_slot < coder->dist_table_size; ++dist_slot)
			dist_slot_prices[dist_slot] = rc_bittree_price(
					coder->dist_slot[dist_state],
					DIST_SLOT_BITS, dist_slot);

		// For matches with distance >= FULL_DISTANCES, add the price
		// of the direct bits part of the match distance. (Align bits
		// are handled by fill_align_prices()).
		for (uint32_t dist_slot = DIST_MODEL_END;
				dist_slot < coder->dist_table_size;
				++dist_slot)
			dist_slot_prices[dist_slot] += rc_direct_price(
					((dist_slot >> 1) - 1) - ALIGN_BITS);

		// Distances in the range [0, 3] are fully encoded with
		// dist_slot, so they are used for coder->dist_prices
		// as is.
		for (uint32_t i = 0; i < DIST_MODEL_START; ++i)
			coder->dist_prices[dist_state][i]
					= dist_slot_prices[i];
	}

	// Distances in the range [4, 127] depend on dist_slot and
	// dist_special. We do this in a loop separate from the above
	// loop to avoid redundant calls to get_dist_slot().
	for (uint32_t i = DIST_MODEL_START; i < FULL_DISTANCES; ++i) {
		const uint32_t dist_slot = get_dist_slot(i);
		const uint32_t footer_bits = ((dist_slot >> 1) - 1);
		const uint32_t base = (2 | (dist_slot & 1)) << footer_bits;
		const uint32_t price = rc_bittree_reverse_price(
				coder->dist_special + base - dist_slot - 1,
				footer_bits, i - base);

		for (uint32_t dist_state = 0; dist_state < DIST_STATES;
				++dist_state)
			coder->dist_prices[dist_state][i]
					= price + coder->dist_slot_prices[
						dist_state][dist_slot];
	}

	coder->match_price_count = 0;
	return;
}