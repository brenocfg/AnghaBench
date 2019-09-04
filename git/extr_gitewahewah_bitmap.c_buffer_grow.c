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
typedef  int /*<<< orphan*/  uint8_t ;
struct ewah_bitmap {size_t alloc_size; scalar_t__ buffer; scalar_t__ rlw; } ;
typedef  int /*<<< orphan*/  eword_t ;

/* Variables and functions */
 int /*<<< orphan*/  REALLOC_ARRAY (scalar_t__,size_t) ; 

__attribute__((used)) static inline void buffer_grow(struct ewah_bitmap *self, size_t new_size)
{
	size_t rlw_offset = (uint8_t *)self->rlw - (uint8_t *)self->buffer;

	if (self->alloc_size >= new_size)
		return;

	self->alloc_size = new_size;
	REALLOC_ARRAY(self->buffer, self->alloc_size);
	self->rlw = self->buffer + (rlw_offset / sizeof(eword_t));
}