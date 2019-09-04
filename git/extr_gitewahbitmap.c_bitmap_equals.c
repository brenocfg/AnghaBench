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
struct bitmap {scalar_t__ word_alloc; scalar_t__* words; } ;

/* Variables and functions */

int bitmap_equals(struct bitmap *self, struct bitmap *other)
{
	struct bitmap *big, *small;
	size_t i;

	if (self->word_alloc < other->word_alloc) {
		small = self;
		big = other;
	} else {
		small = other;
		big = self;
	}

	for (i = 0; i < small->word_alloc; ++i) {
		if (small->words[i] != big->words[i])
			return 0;
	}

	for (; i < big->word_alloc; ++i) {
		if (big->words[i] != 0)
			return 0;
	}

	return 1;
}