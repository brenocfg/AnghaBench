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
struct bitmap {size_t word_alloc; int /*<<< orphan*/ * words; } ;

/* Variables and functions */

void bitmap_and_not(struct bitmap *self, struct bitmap *other)
{
	const size_t count = (self->word_alloc < other->word_alloc) ?
		self->word_alloc : other->word_alloc;

	size_t i;

	for (i = 0; i < count; ++i)
		self->words[i] &= ~other->words[i];
}