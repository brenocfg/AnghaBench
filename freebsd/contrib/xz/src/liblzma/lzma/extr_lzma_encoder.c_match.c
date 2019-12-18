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
struct TYPE_3__ {size_t const dist_special; size_t const dist_align; size_t* reps; int /*<<< orphan*/  match_price_count; int /*<<< orphan*/  align_price_count; int /*<<< orphan*/  rc; int /*<<< orphan*/ * dist_slot; int /*<<< orphan*/  fast_mode; int /*<<< orphan*/  match_len_encoder; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ lzma_lzma1_encoder ;

/* Variables and functions */
 size_t const ALIGN_BITS ; 
 size_t const ALIGN_MASK ; 
 size_t const DIST_MODEL_END ; 
 size_t const DIST_MODEL_START ; 
 int /*<<< orphan*/  DIST_SLOT_BITS ; 
 size_t get_dist_slot (size_t const) ; 
 size_t get_dist_state (size_t const) ; 
 int /*<<< orphan*/  length (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t const,size_t const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_bittree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t const) ; 
 int /*<<< orphan*/  rc_bittree_reverse (int /*<<< orphan*/ *,size_t const,size_t const,size_t const) ; 
 int /*<<< orphan*/  rc_direct (int /*<<< orphan*/ *,size_t const,size_t const) ; 
 int /*<<< orphan*/  update_match (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
match(lzma_lzma1_encoder *coder, const uint32_t pos_state,
		const uint32_t distance, const uint32_t len)
{
	update_match(coder->state);

	length(&coder->rc, &coder->match_len_encoder, pos_state, len,
			coder->fast_mode);

	const uint32_t dist_slot = get_dist_slot(distance);
	const uint32_t dist_state = get_dist_state(len);
	rc_bittree(&coder->rc, coder->dist_slot[dist_state],
			DIST_SLOT_BITS, dist_slot);

	if (dist_slot >= DIST_MODEL_START) {
		const uint32_t footer_bits = (dist_slot >> 1) - 1;
		const uint32_t base = (2 | (dist_slot & 1)) << footer_bits;
		const uint32_t dist_reduced = distance - base;

		if (dist_slot < DIST_MODEL_END) {
			// Careful here: base - dist_slot - 1 can be -1, but
			// rc_bittree_reverse starts at probs[1], not probs[0].
			rc_bittree_reverse(&coder->rc,
				coder->dist_special + base - dist_slot - 1,
				footer_bits, dist_reduced);
		} else {
			rc_direct(&coder->rc, dist_reduced >> ALIGN_BITS,
					footer_bits - ALIGN_BITS);
			rc_bittree_reverse(
					&coder->rc, coder->dist_align,
					ALIGN_BITS, dist_reduced & ALIGN_MASK);
			++coder->align_price_count;
		}
	}

	coder->reps[3] = coder->reps[2];
	coder->reps[2] = coder->reps[1];
	coder->reps[1] = coder->reps[0];
	coder->reps[0] = distance;
	++coder->match_price_count;
}