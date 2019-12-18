#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_4__ {scalar_t__ len; size_t pos_mask; size_t state; int /*<<< orphan*/  rep0; int /*<<< orphan*/ * is_rep; int /*<<< orphan*/ ** is_match; } ;
struct TYPE_5__ {size_t pos; } ;
struct xz_dec_lzma2 {int /*<<< orphan*/  rc; TYPE_1__ lzma; TYPE_2__ dict; } ;

/* Variables and functions */
 scalar_t__ dict_has_space (TYPE_2__*) ; 
 int /*<<< orphan*/  dict_repeat (TYPE_2__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lzma_literal (struct xz_dec_lzma2*) ; 
 int /*<<< orphan*/  lzma_match (struct xz_dec_lzma2*,size_t) ; 
 int /*<<< orphan*/  lzma_rep_match (struct xz_dec_lzma2*,size_t) ; 
 scalar_t__ rc_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rc_limit_exceeded (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rc_normalize (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool lzma_main(struct xz_dec_lzma2 *s)
{
	uint32_t pos_state;

	/*
	 * If the dictionary was reached during the previous call, try to
	 * finish the possibly pending repeat in the dictionary.
	 */
	if (dict_has_space(&s->dict) && s->lzma.len > 0)
		dict_repeat(&s->dict, &s->lzma.len, s->lzma.rep0);

	/*
	 * Decode more LZMA symbols. One iteration may consume up to
	 * LZMA_IN_REQUIRED - 1 bytes.
	 */
	while (dict_has_space(&s->dict) && !rc_limit_exceeded(&s->rc)) {
		pos_state = s->dict.pos & s->lzma.pos_mask;

		if (!rc_bit(&s->rc, &s->lzma.is_match[
				s->lzma.state][pos_state])) {
			lzma_literal(s);
		} else {
			if (rc_bit(&s->rc, &s->lzma.is_rep[s->lzma.state]))
				lzma_rep_match(s, pos_state);
			else
				lzma_match(s, pos_state);

			if (!dict_repeat(&s->dict, &s->lzma.len, s->lzma.rep0))
				return false;
		}
	}

	/*
	 * Having the range decoder always normalized when we are outside
	 * this function makes it easier to correctly handle end of the chunk.
	 */
	rc_normalize(&s->rc);

	return true;
}