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
struct ewah_bitmap {size_t bit_size; size_t* buffer; int buffer_size; int /*<<< orphan*/  rlw; } ;
typedef  size_t eword_t ;

/* Variables and functions */
 size_t BITS_IN_EWORD ; 
 size_t DIV_ROUND_UP (size_t,size_t) ; 
 int /*<<< orphan*/  add_empty_word (struct ewah_bitmap*,int) ; 
 int /*<<< orphan*/  add_empty_words (struct ewah_bitmap*,int /*<<< orphan*/ ,size_t const) ; 
 int /*<<< orphan*/  add_literal (struct ewah_bitmap*,size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ rlw_get_literal_words (int /*<<< orphan*/ ) ; 
 scalar_t__ rlw_get_running_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rlw_set_literal_words (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rlw_set_running_len (int /*<<< orphan*/ ,scalar_t__) ; 

void ewah_set(struct ewah_bitmap *self, size_t i)
{
	const size_t dist =
		DIV_ROUND_UP(i + 1, BITS_IN_EWORD) -
		DIV_ROUND_UP(self->bit_size, BITS_IN_EWORD);

	assert(i >= self->bit_size);

	self->bit_size = i + 1;

	if (dist > 0) {
		if (dist > 1)
			add_empty_words(self, 0, dist - 1);

		add_literal(self, (eword_t)1 << (i % BITS_IN_EWORD));
		return;
	}

	if (rlw_get_literal_words(self->rlw) == 0) {
		rlw_set_running_len(self->rlw,
			rlw_get_running_len(self->rlw) - 1);
		add_literal(self, (eword_t)1 << (i % BITS_IN_EWORD));
		return;
	}

	self->buffer[self->buffer_size - 1] |=
		((eword_t)1 << (i % BITS_IN_EWORD));

	/* check if we just completed a stream of 1s */
	if (self->buffer[self->buffer_size - 1] == (eword_t)(~0)) {
		self->buffer[--self->buffer_size] = 0;
		rlw_set_literal_words(self->rlw,
			rlw_get_literal_words(self->rlw) - 1);
		add_empty_word(self, 1);
	}
}