#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ active; scalar_t__ current; unsigned int used; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ isc_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_BUFFER_VALID (TYPE_1__*) ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 void* isc_buffer_current (TYPE_1__*) ; 
 unsigned int isc_buffer_remaininglength (TYPE_1__*) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,void*,size_t) ; 

void
isc_buffer_compact(isc_buffer_t *b) {
	unsigned int length;
	void *src;

	/*
	 * Compact the used region by moving the remaining region so it occurs
	 * at the start of the buffer.  The used region is shrunk by the size
	 * of the consumed region, and the consumed region is then made empty.
	 */

	REQUIRE(ISC_BUFFER_VALID(b));

	src = isc_buffer_current(b);
	length = isc_buffer_remaininglength(b);
	(void)memmove(b->base, src, (size_t)length);

	if (b->active > b->current)
		b->active -= b->current;
	else
		b->active = 0;
	b->current = 0;
	b->used = length;
}