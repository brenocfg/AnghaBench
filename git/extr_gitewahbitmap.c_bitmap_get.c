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
struct bitmap {size_t word_alloc; int* words; } ;

/* Variables and functions */
 size_t EWAH_BLOCK (size_t) ; 
 int EWAH_MASK (size_t) ; 

int bitmap_get(struct bitmap *self, size_t pos)
{
	size_t block = EWAH_BLOCK(pos);
	return block < self->word_alloc &&
		(self->words[block] & EWAH_MASK(pos)) != 0;
}