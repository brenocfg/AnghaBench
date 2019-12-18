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
struct ewah_bitmap {scalar_t__ alloc_size; } ;

/* Variables and functions */
 scalar_t__ BITMAP_POOL_MAX ; 
 struct ewah_bitmap** bitmap_pool ; 
 scalar_t__ bitmap_pool_size ; 
 int /*<<< orphan*/  ewah_clear (struct ewah_bitmap*) ; 
 int /*<<< orphan*/  ewah_free (struct ewah_bitmap*) ; 

void ewah_pool_free(struct ewah_bitmap *self)
{
	if (self == NULL)
		return;

	if (bitmap_pool_size == BITMAP_POOL_MAX ||
		self->alloc_size == 0) {
		ewah_free(self);
		return;
	}

	ewah_clear(self);
	bitmap_pool[bitmap_pool_size++] = self;
}