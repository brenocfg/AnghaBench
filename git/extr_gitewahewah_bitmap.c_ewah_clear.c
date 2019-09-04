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
struct ewah_bitmap {int buffer_size; scalar_t__* buffer; scalar_t__* rlw; scalar_t__ bit_size; } ;

/* Variables and functions */

__attribute__((used)) static void ewah_clear(struct ewah_bitmap *self)
{
	self->buffer_size = 1;
	self->buffer[0] = 0;
	self->bit_size = 0;
	self->rlw = self->buffer;
}