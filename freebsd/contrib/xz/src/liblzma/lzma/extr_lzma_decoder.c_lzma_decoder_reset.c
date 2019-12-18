#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_7__ {unsigned int pb; unsigned int lp; int /*<<< orphan*/  lc; } ;
typedef  TYPE_3__ lzma_options_lzma ;
struct TYPE_6__ {int /*<<< orphan*/  high; int /*<<< orphan*/ * mid; int /*<<< orphan*/ * low; int /*<<< orphan*/  choice2; int /*<<< orphan*/  choice; } ;
struct TYPE_5__ {int /*<<< orphan*/  high; int /*<<< orphan*/ * mid; int /*<<< orphan*/ * low; int /*<<< orphan*/  choice2; int /*<<< orphan*/  choice; } ;
struct TYPE_8__ {unsigned int pos_mask; unsigned int literal_pos_mask; scalar_t__ len; scalar_t__ offset; scalar_t__ limit; scalar_t__ symbol; int /*<<< orphan*/ * probs; int /*<<< orphan*/  sequence; TYPE_2__ rep_len_decoder; TYPE_1__ match_len_decoder; int /*<<< orphan*/  pos_align; int /*<<< orphan*/ * pos_special; int /*<<< orphan*/ * dist_slot; int /*<<< orphan*/ * is_rep2; int /*<<< orphan*/ * is_rep1; int /*<<< orphan*/ * is_rep0; int /*<<< orphan*/ * is_rep; int /*<<< orphan*/ ** is_rep0_long; int /*<<< orphan*/ ** is_match; int /*<<< orphan*/  rc; scalar_t__ rep3; scalar_t__ rep2; scalar_t__ rep1; scalar_t__ rep0; int /*<<< orphan*/  state; int /*<<< orphan*/  literal_context_bits; int /*<<< orphan*/  literal; } ;
typedef  TYPE_4__ lzma_lzma1_decoder ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN_BITS ; 
 size_t DIST_MODEL_END ; 
 int /*<<< orphan*/  DIST_SLOT_BITS ; 
 size_t DIST_STATES ; 
 size_t FULL_DISTANCES ; 
 int /*<<< orphan*/  LEN_HIGH_BITS ; 
 int /*<<< orphan*/  LEN_LOW_BITS ; 
 int /*<<< orphan*/  LEN_MID_BITS ; 
 int /*<<< orphan*/  SEQ_IS_MATCH ; 
 size_t STATES ; 
 int /*<<< orphan*/  STATE_LIT_LIT ; 
 int /*<<< orphan*/  bit_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bittree_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  literal_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  rc_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lzma_decoder_reset(void *coder_ptr, const void *opt)
{
	lzma_lzma1_decoder *coder = coder_ptr;
	const lzma_options_lzma *options = opt;

	// NOTE: We assume that lc/lp/pb are valid since they were
	// successfully decoded with lzma_lzma_decode_properties().

	// Calculate pos_mask. We don't need pos_bits as is for anything.
	coder->pos_mask = (1U << options->pb) - 1;

	// Initialize the literal decoder.
	literal_init(coder->literal, options->lc, options->lp);

	coder->literal_context_bits = options->lc;
	coder->literal_pos_mask = (1U << options->lp) - 1;

	// State
	coder->state = STATE_LIT_LIT;
	coder->rep0 = 0;
	coder->rep1 = 0;
	coder->rep2 = 0;
	coder->rep3 = 0;
	coder->pos_mask = (1U << options->pb) - 1;

	// Range decoder
	rc_reset(coder->rc);

	// Bit and bittree decoders
	for (uint32_t i = 0; i < STATES; ++i) {
		for (uint32_t j = 0; j <= coder->pos_mask; ++j) {
			bit_reset(coder->is_match[i][j]);
			bit_reset(coder->is_rep0_long[i][j]);
		}

		bit_reset(coder->is_rep[i]);
		bit_reset(coder->is_rep0[i]);
		bit_reset(coder->is_rep1[i]);
		bit_reset(coder->is_rep2[i]);
	}

	for (uint32_t i = 0; i < DIST_STATES; ++i)
		bittree_reset(coder->dist_slot[i], DIST_SLOT_BITS);

	for (uint32_t i = 0; i < FULL_DISTANCES - DIST_MODEL_END; ++i)
		bit_reset(coder->pos_special[i]);

	bittree_reset(coder->pos_align, ALIGN_BITS);

	// Len decoders (also bit/bittree)
	const uint32_t num_pos_states = 1U << options->pb;
	bit_reset(coder->match_len_decoder.choice);
	bit_reset(coder->match_len_decoder.choice2);
	bit_reset(coder->rep_len_decoder.choice);
	bit_reset(coder->rep_len_decoder.choice2);

	for (uint32_t pos_state = 0; pos_state < num_pos_states; ++pos_state) {
		bittree_reset(coder->match_len_decoder.low[pos_state],
				LEN_LOW_BITS);
		bittree_reset(coder->match_len_decoder.mid[pos_state],
				LEN_MID_BITS);

		bittree_reset(coder->rep_len_decoder.low[pos_state],
				LEN_LOW_BITS);
		bittree_reset(coder->rep_len_decoder.mid[pos_state],
				LEN_MID_BITS);
	}

	bittree_reset(coder->match_len_decoder.high, LEN_HIGH_BITS);
	bittree_reset(coder->rep_len_decoder.high, LEN_HIGH_BITS);

	coder->sequence = SEQ_IS_MATCH;
	coder->probs = NULL;
	coder->symbol = 0;
	coder->limit = 0;
	coder->offset = 0;
	coder->len = 0;

	return;
}