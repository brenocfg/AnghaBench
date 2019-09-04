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
struct ewah_bitmap {size_t buffer_size; size_t alloc_size; size_t bit_size; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  rlw; } ;
typedef  int /*<<< orphan*/  eword_t ;

/* Variables and functions */
 size_t BITS_IN_EWORD ; 
 scalar_t__ RLW_LARGEST_LITERAL_COUNT ; 
 int /*<<< orphan*/  buffer_grow (struct ewah_bitmap*,size_t) ; 
 int /*<<< orphan*/  buffer_push_rlw (struct ewah_bitmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 size_t min_size (size_t,scalar_t__) ; 
 size_t rlw_get_literal_words (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rlw_set_literal_words (int /*<<< orphan*/ ,size_t) ; 

void ewah_add_dirty_words(
	struct ewah_bitmap *self, const eword_t *buffer,
	size_t number, int negate)
{
	size_t literals, can_add;

	while (1) {
		literals = rlw_get_literal_words(self->rlw);
		can_add = min_size(number, RLW_LARGEST_LITERAL_COUNT - literals);

		rlw_set_literal_words(self->rlw, literals + can_add);

		if (self->buffer_size + can_add >= self->alloc_size)
			buffer_grow(self, (self->buffer_size + can_add) * 3 / 2);

		if (negate) {
			size_t i;
			for (i = 0; i < can_add; ++i)
				self->buffer[self->buffer_size++] = ~buffer[i];
		} else {
			memcpy(self->buffer + self->buffer_size,
				buffer, can_add * sizeof(eword_t));
			self->buffer_size += can_add;
		}

		self->bit_size += can_add * BITS_IN_EWORD;

		if (number - can_add == 0)
			break;

		buffer_push_rlw(self, 0);
		buffer += can_add;
		number -= can_add;
	}
}