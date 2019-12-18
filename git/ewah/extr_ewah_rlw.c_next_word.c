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
struct TYPE_2__ {scalar_t__ literal_word_offset; int /*<<< orphan*/ * word; int /*<<< orphan*/  running_bit; int /*<<< orphan*/  running_len; scalar_t__ literal_words; } ;
struct rlw_iterator {size_t pointer; size_t size; TYPE_1__ rlw; int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 scalar_t__ rlw_get_literal_words (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rlw_get_run_bit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rlw_get_running_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int next_word(struct rlw_iterator *it)
{
	if (it->pointer >= it->size)
		return 0;

	it->rlw.word = &it->buffer[it->pointer];
	it->pointer += rlw_get_literal_words(it->rlw.word) + 1;

	it->rlw.literal_words = rlw_get_literal_words(it->rlw.word);
	it->rlw.running_len = rlw_get_running_len(it->rlw.word);
	it->rlw.running_bit = rlw_get_run_bit(it->rlw.word);
	it->rlw.literal_word_offset = 0;

	return 1;
}