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
typedef  int uint8_t ;
struct TYPE_2__ {int pos_mask; int literal_pos_mask; int lc; } ;
struct xz_dec_lzma2 {TYPE_1__ lzma; } ;

/* Variables and functions */
 int /*<<< orphan*/  lzma_reset (struct xz_dec_lzma2*) ; 

__attribute__((used)) static bool lzma_props(struct xz_dec_lzma2 *s, uint8_t props)
{
	if (props > (4 * 5 + 4) * 9 + 8)
		return false;

	s->lzma.pos_mask = 0;
	while (props >= 9 * 5) {
		props -= 9 * 5;
		++s->lzma.pos_mask;
	}

	s->lzma.pos_mask = (1 << s->lzma.pos_mask) - 1;

	s->lzma.literal_pos_mask = 0;
	while (props >= 9) {
		props -= 9;
		++s->lzma.literal_pos_mask;
	}

	s->lzma.lc = props;

	if (s->lzma.lc + s->lzma.literal_pos_mask > 4)
		return false;

	s->lzma.literal_pos_mask = (1 << s->lzma.literal_pos_mask) - 1;

	lzma_reset(s);

	return true;
}