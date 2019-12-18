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
struct TYPE_2__ {scalar_t__ running_len; int /*<<< orphan*/  literal_words; int /*<<< orphan*/  running_bit; } ;
struct rlw_iterator {int* buffer; size_t literal_word_start; TYPE_1__ rlw; } ;
struct ewah_bitmap {int /*<<< orphan*/  bit_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ewah_add (struct ewah_bitmap*,int) ; 
 int /*<<< orphan*/  ewah_add_empty_words (struct ewah_bitmap*,int,scalar_t__) ; 
 int /*<<< orphan*/  max_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t min_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rlwit_discard_first_words (struct rlw_iterator*,size_t) ; 
 size_t rlwit_discharge (struct rlw_iterator*,struct ewah_bitmap*,scalar_t__,int) ; 
 int /*<<< orphan*/  rlwit_init (struct rlw_iterator*,struct ewah_bitmap*) ; 
 scalar_t__ rlwit_word_size (struct rlw_iterator*) ; 

void ewah_xor(
	struct ewah_bitmap *ewah_i,
	struct ewah_bitmap *ewah_j,
	struct ewah_bitmap *out)
{
	struct rlw_iterator rlw_i;
	struct rlw_iterator rlw_j;
	size_t literals;

	rlwit_init(&rlw_i, ewah_i);
	rlwit_init(&rlw_j, ewah_j);

	while (rlwit_word_size(&rlw_i) > 0 && rlwit_word_size(&rlw_j) > 0) {
		while (rlw_i.rlw.running_len > 0 || rlw_j.rlw.running_len > 0) {
			struct rlw_iterator *prey, *predator;
			size_t index;
			int negate_words;

			if (rlw_i.rlw.running_len < rlw_j.rlw.running_len) {
				prey = &rlw_i;
				predator = &rlw_j;
			} else {
				prey = &rlw_j;
				predator = &rlw_i;
			}

			negate_words = !!predator->rlw.running_bit;
			index = rlwit_discharge(prey, out,
				predator->rlw.running_len, negate_words);

			ewah_add_empty_words(out, negate_words,
				predator->rlw.running_len - index);

			rlwit_discard_first_words(predator,
				predator->rlw.running_len);
		}

		literals = min_size(
			rlw_i.rlw.literal_words,
			rlw_j.rlw.literal_words);

		if (literals) {
			size_t k;

			for (k = 0; k < literals; ++k) {
				ewah_add(out,
					rlw_i.buffer[rlw_i.literal_word_start + k] ^
					rlw_j.buffer[rlw_j.literal_word_start + k]
				);
			}

			rlwit_discard_first_words(&rlw_i, literals);
			rlwit_discard_first_words(&rlw_j, literals);
		}
	}

	if (rlwit_word_size(&rlw_i) > 0)
		rlwit_discharge(&rlw_i, out, ~0, 0);
	else
		rlwit_discharge(&rlw_j, out, ~0, 0);

	out->bit_size = max_size(ewah_i->bit_size, ewah_j->bit_size);
}