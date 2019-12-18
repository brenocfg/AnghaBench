#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_6__ {unsigned int pb; unsigned int lp; int /*<<< orphan*/  lc; } ;
typedef  TYPE_1__ lzma_options_lzma ;
struct TYPE_7__ {unsigned int pos_mask; unsigned int literal_pos_mask; int match_price_count; int align_price_count; scalar_t__ opts_current_index; scalar_t__ opts_end_index; int /*<<< orphan*/  fast_mode; int /*<<< orphan*/  rep_len_encoder; int /*<<< orphan*/  match_len_encoder; int /*<<< orphan*/  dist_align; int /*<<< orphan*/ * dist_slot; int /*<<< orphan*/ * dist_special; int /*<<< orphan*/ * is_rep2; int /*<<< orphan*/ * is_rep1; int /*<<< orphan*/ * is_rep0; int /*<<< orphan*/ * is_rep; int /*<<< orphan*/ ** is_rep0_long; int /*<<< orphan*/ ** is_match; int /*<<< orphan*/  literal; scalar_t__* reps; int /*<<< orphan*/  state; int /*<<< orphan*/  rc; int /*<<< orphan*/  literal_context_bits; } ;
typedef  TYPE_2__ lzma_lzma1_encoder ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN_BITS ; 
 size_t DIST_MODEL_END ; 
 int /*<<< orphan*/  DIST_SLOT_BITS ; 
 size_t DIST_STATES ; 
 size_t FULL_DISTANCES ; 
 int /*<<< orphan*/  LZMA_OK ; 
 int /*<<< orphan*/  LZMA_OPTIONS_ERROR ; 
 size_t REPS ; 
 size_t STATES ; 
 int /*<<< orphan*/  STATE_LIT_LIT ; 
 int UINT32_MAX ; 
 int /*<<< orphan*/  bit_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bittree_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_options_valid (TYPE_1__ const*) ; 
 int /*<<< orphan*/  length_encoder_reset (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  literal_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  rc_reset (int /*<<< orphan*/ *) ; 

extern lzma_ret
lzma_lzma_encoder_reset(lzma_lzma1_encoder *coder,
		const lzma_options_lzma *options)
{
	if (!is_options_valid(options))
		return LZMA_OPTIONS_ERROR;

	coder->pos_mask = (1U << options->pb) - 1;
	coder->literal_context_bits = options->lc;
	coder->literal_pos_mask = (1U << options->lp) - 1;

	// Range coder
	rc_reset(&coder->rc);

	// State
	coder->state = STATE_LIT_LIT;
	for (size_t i = 0; i < REPS; ++i)
		coder->reps[i] = 0;

	literal_init(coder->literal, options->lc, options->lp);

	// Bit encoders
	for (size_t i = 0; i < STATES; ++i) {
		for (size_t j = 0; j <= coder->pos_mask; ++j) {
			bit_reset(coder->is_match[i][j]);
			bit_reset(coder->is_rep0_long[i][j]);
		}

		bit_reset(coder->is_rep[i]);
		bit_reset(coder->is_rep0[i]);
		bit_reset(coder->is_rep1[i]);
		bit_reset(coder->is_rep2[i]);
	}

	for (size_t i = 0; i < FULL_DISTANCES - DIST_MODEL_END; ++i)
		bit_reset(coder->dist_special[i]);

	// Bit tree encoders
	for (size_t i = 0; i < DIST_STATES; ++i)
		bittree_reset(coder->dist_slot[i], DIST_SLOT_BITS);

	bittree_reset(coder->dist_align, ALIGN_BITS);

	// Length encoders
	length_encoder_reset(&coder->match_len_encoder,
			1U << options->pb, coder->fast_mode);

	length_encoder_reset(&coder->rep_len_encoder,
			1U << options->pb, coder->fast_mode);

	// Price counts are incremented every time appropriate probabilities
	// are changed. price counts are set to zero when the price tables
	// are updated, which is done when the appropriate price counts have
	// big enough value, and lzma_mf.read_ahead == 0 which happens at
	// least every OPTS (a few thousand) possible price count increments.
	//
	// By resetting price counts to UINT32_MAX / 2, we make sure that the
	// price tables will be initialized before they will be used (since
	// the value is definitely big enough), and that it is OK to increment
	// price counts without risk of integer overflow (since UINT32_MAX / 2
	// is small enough). The current code doesn't increment price counts
	// before initializing price tables, but it maybe done in future if
	// we add support for saving the state between LZMA2 chunks.
	coder->match_price_count = UINT32_MAX / 2;
	coder->align_price_count = UINT32_MAX / 2;

	coder->opts_end_index = 0;
	coder->opts_current_index = 0;

	return LZMA_OK;
}