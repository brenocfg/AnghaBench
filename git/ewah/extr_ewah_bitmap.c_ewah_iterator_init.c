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
struct ewah_iterator {scalar_t__ buffer_size; scalar_t__ pointer; scalar_t__ b; scalar_t__ literals; scalar_t__ compressed; scalar_t__ rl; scalar_t__ lw; int /*<<< orphan*/  buffer; } ;
struct ewah_bitmap {scalar_t__ buffer_size; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  read_new_rlw (struct ewah_iterator*) ; 

void ewah_iterator_init(struct ewah_iterator *it, struct ewah_bitmap *parent)
{
	it->buffer = parent->buffer;
	it->buffer_size = parent->buffer_size;
	it->pointer = 0;

	it->lw = 0;
	it->rl = 0;
	it->compressed = 0;
	it->literals = 0;
	it->b = 0;

	if (it->pointer < it->buffer_size)
		read_new_rlw(it);
}