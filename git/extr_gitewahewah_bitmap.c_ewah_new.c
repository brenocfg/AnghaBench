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
struct ewah_bitmap {int alloc_size; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_ARRAY (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ewah_clear (struct ewah_bitmap*) ; 
 struct ewah_bitmap* xmalloc (int) ; 

struct ewah_bitmap *ewah_new(void)
{
	struct ewah_bitmap *self;

	self = xmalloc(sizeof(struct ewah_bitmap));
	self->alloc_size = 32;
	ALLOC_ARRAY(self->buffer, self->alloc_size);

	ewah_clear(self);
	return self;
}