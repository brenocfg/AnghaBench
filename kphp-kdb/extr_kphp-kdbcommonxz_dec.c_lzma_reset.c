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
typedef  int uint16_t ;
struct TYPE_2__ {int** is_match; scalar_t__ rep3; scalar_t__ rep2; scalar_t__ rep1; scalar_t__ rep0; int /*<<< orphan*/  state; } ;
struct xz_dec_lzma2 {int /*<<< orphan*/  rc; TYPE_1__ lzma; } ;

/* Variables and functions */
 size_t PROBS_TOTAL ; 
 int RC_BIT_MODEL_TOTAL ; 
 int /*<<< orphan*/  STATE_LIT_LIT ; 
 int /*<<< orphan*/  rc_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lzma_reset(struct xz_dec_lzma2 *s)
{
	uint16_t *probs;
	size_t i;

	s->lzma.state = STATE_LIT_LIT;
	s->lzma.rep0 = 0;
	s->lzma.rep1 = 0;
	s->lzma.rep2 = 0;
	s->lzma.rep3 = 0;

	/*
	 * All probabilities are initialized to the same value. This hack
	 * makes the code smaller by avoiding a separate loop for each
	 * probability array.
	 *
	 * This could be optimized so that only that part of literal
	 * probabilities that are actually required. In the common case
	 * we would write 12 KiB less.
	 */
	probs = s->lzma.is_match[0];
	for (i = 0; i < PROBS_TOTAL; ++i)
		probs[i] = RC_BIT_MODEL_TOTAL / 2;

	rc_reset(&s->rc);
}