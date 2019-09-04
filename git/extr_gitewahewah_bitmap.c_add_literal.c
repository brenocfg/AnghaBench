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
struct ewah_bitmap {int /*<<< orphan*/  rlw; } ;
typedef  int eword_t ;

/* Variables and functions */
 int RLW_LARGEST_LITERAL_COUNT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  buffer_push (struct ewah_bitmap*,int) ; 
 int /*<<< orphan*/  buffer_push_rlw (struct ewah_bitmap*,int /*<<< orphan*/ ) ; 
 int rlw_get_literal_words (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rlw_set_literal_words (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static size_t add_literal(struct ewah_bitmap *self, eword_t new_data)
{
	eword_t current_num = rlw_get_literal_words(self->rlw);

	if (current_num >= RLW_LARGEST_LITERAL_COUNT) {
		buffer_push_rlw(self, 0);

		rlw_set_literal_words(self->rlw, 1);
		buffer_push(self, new_data);
		return 2;
	}

	rlw_set_literal_words(self->rlw, current_num + 1);

	/* sanity check */
	assert(rlw_get_literal_words(self->rlw) == current_num + 1);

	buffer_push(self, new_data);
	return 1;
}