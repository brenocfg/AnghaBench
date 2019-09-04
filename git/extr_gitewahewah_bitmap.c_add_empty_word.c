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
typedef  scalar_t__ eword_t ;

/* Variables and functions */
 scalar_t__ RLW_LARGEST_RUNNING_COUNT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  buffer_push_rlw (struct ewah_bitmap*,int /*<<< orphan*/ ) ; 
 scalar_t__ rlw_get_literal_words (int /*<<< orphan*/ ) ; 
 int rlw_get_run_bit (int /*<<< orphan*/ ) ; 
 int rlw_get_running_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rlw_set_run_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rlw_set_running_len (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static size_t add_empty_word(struct ewah_bitmap *self, int v)
{
	int no_literal = (rlw_get_literal_words(self->rlw) == 0);
	eword_t run_len = rlw_get_running_len(self->rlw);

	if (no_literal && run_len == 0) {
		rlw_set_run_bit(self->rlw, v);
		assert(rlw_get_run_bit(self->rlw) == v);
	}

	if (no_literal && rlw_get_run_bit(self->rlw) == v &&
		run_len < RLW_LARGEST_RUNNING_COUNT) {
		rlw_set_running_len(self->rlw, run_len + 1);
		assert(rlw_get_running_len(self->rlw) == run_len + 1);
		return 0;
	} else {
		buffer_push_rlw(self, 0);

		assert(rlw_get_running_len(self->rlw) == 0);
		assert(rlw_get_run_bit(self->rlw) == 0);
		assert(rlw_get_literal_words(self->rlw) == 0);

		rlw_set_run_bit(self->rlw, v);
		assert(rlw_get_run_bit(self->rlw) == v);

		rlw_set_running_len(self->rlw, 1);
		assert(rlw_get_running_len(self->rlw) == 1);
		assert(rlw_get_literal_words(self->rlw) == 0);
		return 1;
	}
}