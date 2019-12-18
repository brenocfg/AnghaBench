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
struct ewah_bitmap {int /*<<< orphan*/  bit_size; } ;
typedef  scalar_t__ eword_t ;

/* Variables and functions */
 scalar_t__ BITS_IN_EWORD ; 
 size_t add_empty_word (struct ewah_bitmap*,int) ; 
 size_t add_literal (struct ewah_bitmap*,scalar_t__) ; 

size_t ewah_add(struct ewah_bitmap *self, eword_t word)
{
	self->bit_size += BITS_IN_EWORD;

	if (word == 0)
		return add_empty_word(self, 0);

	if (word == (eword_t)(~0))
		return add_empty_word(self, 1);

	return add_literal(self, word);
}