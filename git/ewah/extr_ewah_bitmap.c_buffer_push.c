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
struct ewah_bitmap {int buffer_size; int alloc_size; int /*<<< orphan*/ * buffer; } ;
typedef  int /*<<< orphan*/  eword_t ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_grow (struct ewah_bitmap*,int) ; 

__attribute__((used)) static inline void buffer_push(struct ewah_bitmap *self, eword_t value)
{
	if (self->buffer_size + 1 >= self->alloc_size)
		buffer_grow(self, self->buffer_size * 3 / 2);

	self->buffer[self->buffer_size++] = value;
}