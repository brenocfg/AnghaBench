#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_2__ {size_t state; int len; size_t rep1; size_t rep2; size_t rep3; size_t rep0; int /*<<< orphan*/  rep_len_dec; int /*<<< orphan*/ * is_rep2; int /*<<< orphan*/ * is_rep1; int /*<<< orphan*/ ** is_rep0_long; int /*<<< orphan*/ * is_rep0; } ;
struct xz_dec_lzma2 {TYPE_1__ lzma; int /*<<< orphan*/  rc; } ;

/* Variables and functions */
 int /*<<< orphan*/  lzma_len (struct xz_dec_lzma2*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  lzma_state_long_rep (size_t*) ; 
 int /*<<< orphan*/  lzma_state_short_rep (size_t*) ; 
 int /*<<< orphan*/  rc_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lzma_rep_match(struct xz_dec_lzma2 *s, uint32_t pos_state)
{
	uint32_t tmp;

	if (!rc_bit(&s->rc, &s->lzma.is_rep0[s->lzma.state])) {
		if (!rc_bit(&s->rc, &s->lzma.is_rep0_long[
				s->lzma.state][pos_state])) {
			lzma_state_short_rep(&s->lzma.state);
			s->lzma.len = 1;
			return;
		}
	} else {
		if (!rc_bit(&s->rc, &s->lzma.is_rep1[s->lzma.state])) {
			tmp = s->lzma.rep1;
		} else {
			if (!rc_bit(&s->rc, &s->lzma.is_rep2[s->lzma.state])) {
				tmp = s->lzma.rep2;
			} else {
				tmp = s->lzma.rep3;
				s->lzma.rep3 = s->lzma.rep2;
			}

			s->lzma.rep2 = s->lzma.rep1;
		}

		s->lzma.rep1 = s->lzma.rep0;
		s->lzma.rep0 = tmp;
	}

	lzma_state_long_rep(&s->lzma.state);
	lzma_len(s, &s->lzma.rep_len_dec, pos_state);
}