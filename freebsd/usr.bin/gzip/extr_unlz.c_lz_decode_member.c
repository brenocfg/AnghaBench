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
struct lz_range_decoder {int dummy; } ;
struct lz_len_model {int dummy; } ;
struct lz_decoder {unsigned int dict_size; unsigned int pos; int /*<<< orphan*/  wrapped; int /*<<< orphan*/  fin; struct lz_range_decoder rdec; } ;

/* Variables and functions */
 int const DIS_ALIGN_BITS ; 
 int DIS_ALIGN_SIZE ; 
 unsigned int const DIS_MODEL_END ; 
 unsigned int DIS_MODEL_START ; 
 int DIS_SLOT_BITS ; 
 int LITERAL_CONTEXT_BITS ; 
 int /*<<< orphan*/  LZ_BM_INIT (int*) ; 
 int /*<<< orphan*/  LZ_BM_INIT2 (int**) ; 
 int /*<<< orphan*/  LZ_MODEL_INIT (struct lz_len_model) ; 
 int LZ_STATES ; 
 int MIN (int,scalar_t__) ; 
 int MIN_MATCH_LEN ; 
 int /*<<< orphan*/  MODELED_DISTANCES ; 
 int POS_STATES ; 
 int POS_STATE_MASK ; 
 scalar_t__ STATES ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lz_flush (struct lz_decoder*) ; 
 int lz_get_data_position (struct lz_decoder*) ; 
 void* lz_peek (struct lz_decoder*,unsigned int) ; 
 int /*<<< orphan*/  lz_put (struct lz_decoder*,void*) ; 
 int const lz_rd_decode (struct lz_range_decoder*,int const) ; 
 scalar_t__ lz_rd_decode_bit (struct lz_range_decoder*,int*) ; 
 int lz_rd_decode_len (struct lz_range_decoder*,struct lz_len_model*,int const) ; 
 void* lz_rd_decode_matched (struct lz_range_decoder*,int*,int) ; 
 void* lz_rd_decode_tree (struct lz_range_decoder*,int*,int) ; 
 scalar_t__ lz_rd_decode_tree_reversed (struct lz_range_decoder*,int*,int const) ; 
 int lz_st_get_char (int) ; 
 int lz_st_get_match (int) ; 
 int lz_st_get_rep (int) ; 
 int lz_st_get_short_rep (int) ; 
 scalar_t__ lz_st_is_char (int) ; 

__attribute__((used)) static bool
lz_decode_member(struct lz_decoder *lz)
{
	int bm_literal[1 << LITERAL_CONTEXT_BITS][0x300];
	int bm_match[LZ_STATES][POS_STATES];
	int bm_rep[4][LZ_STATES];
	int bm_len[LZ_STATES][POS_STATES];
	int bm_dis_slot[LZ_STATES][1 << DIS_SLOT_BITS];
	int bm_dis[MODELED_DISTANCES - DIS_MODEL_END + 1];
	int bm_align[DIS_ALIGN_SIZE];

	LZ_BM_INIT2(bm_literal);
	LZ_BM_INIT2(bm_match);
	LZ_BM_INIT2(bm_rep);
	LZ_BM_INIT2(bm_len);
	LZ_BM_INIT2(bm_dis_slot);
	LZ_BM_INIT(bm_dis);
	LZ_BM_INIT(bm_align);

	struct lz_len_model match_len_model;
	struct lz_len_model rep_len_model;

	LZ_MODEL_INIT(match_len_model);
	LZ_MODEL_INIT(rep_len_model);

	struct lz_range_decoder *rd = &lz->rdec;
	unsigned rep[4] = { 0 };


	int state = 0;

	while (!feof(lz->fin) && !ferror(lz->fin)) {
		const int pos_state = lz_get_data_position(lz) & POS_STATE_MASK;
		// bit 1
		if (lz_rd_decode_bit(rd, &bm_match[state][pos_state]) == 0) {
			const uint8_t prev_byte = lz_peek(lz, 0);
			const int literal_state =
			    prev_byte >> (8 - LITERAL_CONTEXT_BITS);
			int *bm = bm_literal[literal_state];
			if (lz_st_is_char(state))
				lz_put(lz, lz_rd_decode_tree(rd, bm, 8));
			else {
				int peek = lz_peek(lz, rep[0]);
				lz_put(lz, lz_rd_decode_matched(rd, bm, peek));
			}
			state = lz_st_get_char(state);
			continue;
		}
		int len;
		// bit 2
		if (lz_rd_decode_bit(rd, &bm_rep[0][state]) != 0) {
			// bit 3
			if (lz_rd_decode_bit(rd, &bm_rep[1][state]) == 0) {
				// bit 4
				if (lz_rd_decode_bit(rd,
				    &bm_len[state][pos_state]) == 0)
				{
					state = lz_st_get_short_rep(state);
					lz_put(lz, lz_peek(lz, rep[0]));
					continue;
				}
			} else {
				unsigned distance;
				// bit 4
				if (lz_rd_decode_bit(rd, &bm_rep[2][state])
				    == 0)
					distance = rep[1];
				else {
					// bit 5
					if (lz_rd_decode_bit(rd,
					    &bm_rep[3][state]) == 0)
						distance = rep[2];
					else {
						distance = rep[3];
						rep[3] = rep[2];
					}
					rep[2] = rep[1];
				}
				rep[1] = rep[0];
				rep[0] = distance;
			}
			state = lz_st_get_rep(state);
			len = MIN_MATCH_LEN +
			    lz_rd_decode_len(rd, &rep_len_model, pos_state);
		} else {
			rep[3] = rep[2]; rep[2] = rep[1]; rep[1] = rep[0];
			len = MIN_MATCH_LEN +
			    lz_rd_decode_len(rd, &match_len_model, pos_state);
			const int len_state =
			    MIN(len - MIN_MATCH_LEN, STATES - 1);
			rep[0] = lz_rd_decode_tree(rd, bm_dis_slot[len_state],
			    DIS_SLOT_BITS);
			if (rep[0] >= DIS_MODEL_START) {
				const unsigned dis_slot = rep[0];
				const int direct_bits = (dis_slot >> 1) - 1;
			        rep[0] = (2 | (dis_slot & 1)) << direct_bits;
				if (dis_slot < DIS_MODEL_END)
					rep[0] += lz_rd_decode_tree_reversed(rd,
					    &bm_dis[rep[0] - dis_slot],
                                            direct_bits);
				else {
					rep[0] += lz_rd_decode(rd, direct_bits
					    - DIS_ALIGN_BITS) << DIS_ALIGN_BITS;
					rep[0] += lz_rd_decode_tree_reversed(rd,
					    bm_align, DIS_ALIGN_BITS);
					if (rep[0] == 0xFFFFFFFFU) {
						lz_flush(lz);
						return len == MIN_MATCH_LEN;
					}
				}
			}
			state = lz_st_get_match(state);
			if (rep[0] >= lz->dict_size ||
			    (rep[0] >= lz->pos && !lz->wrapped)) {
				lz_flush(lz);
				return false;
			}
		}
		for (int i = 0; i < len; i++)
			lz_put(lz, lz_peek(lz, rep[0]));
    	}
	lz_flush(lz);
	return false;
}