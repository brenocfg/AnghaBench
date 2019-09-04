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
struct ewah_iterator {int dummy; } ;
struct ewah_bitmap {int bit_size; } ;
struct bitmap {size_t word_alloc; int /*<<< orphan*/ * words; } ;
typedef  int /*<<< orphan*/  eword_t ;

/* Variables and functions */
 int BITS_IN_EWORD ; 
 int /*<<< orphan*/  REALLOC_ARRAY (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ewah_iterator_init (struct ewah_iterator*,struct ewah_bitmap*) ; 
 scalar_t__ ewah_iterator_next (int /*<<< orphan*/ *,struct ewah_iterator*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,size_t) ; 

void bitmap_or_ewah(struct bitmap *self, struct ewah_bitmap *other)
{
	size_t original_size = self->word_alloc;
	size_t other_final = (other->bit_size / BITS_IN_EWORD) + 1;
	size_t i = 0;
	struct ewah_iterator it;
	eword_t word;

	if (self->word_alloc < other_final) {
		self->word_alloc = other_final;
		REALLOC_ARRAY(self->words, self->word_alloc);
		memset(self->words + original_size, 0x0,
			(self->word_alloc - original_size) * sizeof(eword_t));
	}

	ewah_iterator_init(&it, other);

	while (ewah_iterator_next(&word, &it))
		self->words[i++] |= word;
}