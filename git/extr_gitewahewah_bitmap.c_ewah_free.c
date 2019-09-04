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
struct ewah_bitmap {struct ewah_bitmap* buffer; scalar_t__ alloc_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ewah_bitmap*) ; 

void ewah_free(struct ewah_bitmap *self)
{
	if (!self)
		return;

	if (self->alloc_size)
		free(self->buffer);

	free(self);
}