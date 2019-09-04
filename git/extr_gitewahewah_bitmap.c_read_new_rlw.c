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
struct ewah_iterator {size_t pointer; int buffer_size; int /*<<< orphan*/  lw; int /*<<< orphan*/  rl; int /*<<< orphan*/  b; int /*<<< orphan*/ * buffer; scalar_t__ compressed; scalar_t__ literals; } ;
typedef  int /*<<< orphan*/  eword_t ;

/* Variables and functions */
 int /*<<< orphan*/  rlw_get_literal_words (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  rlw_get_run_bit (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  rlw_get_running_len (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void read_new_rlw(struct ewah_iterator *it)
{
	const eword_t *word = NULL;

	it->literals = 0;
	it->compressed = 0;

	while (1) {
		word = &it->buffer[it->pointer];

		it->rl = rlw_get_running_len(word);
		it->lw = rlw_get_literal_words(word);
		it->b = rlw_get_run_bit(word);

		if (it->rl || it->lw)
			return;

		if (it->pointer < it->buffer_size - 1) {
			it->pointer++;
		} else {
			it->pointer = it->buffer_size;
			return;
		}
	}
}