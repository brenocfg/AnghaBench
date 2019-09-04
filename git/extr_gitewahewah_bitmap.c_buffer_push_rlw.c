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
struct ewah_bitmap {scalar_t__ buffer_size; scalar_t__ buffer; scalar_t__ rlw; } ;
typedef  int /*<<< orphan*/  eword_t ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_push (struct ewah_bitmap*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void buffer_push_rlw(struct ewah_bitmap *self, eword_t value)
{
	buffer_push(self, value);
	self->rlw = self->buffer + self->buffer_size - 1;
}