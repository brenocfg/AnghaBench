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

/* Variables and functions */
 scalar_t__ HEAP_SIZE ; 
 int /*<<< orphan*/  bzero (scalar_t__,scalar_t__) ; 
 scalar_t__ heap ; 
 int /*<<< orphan*/  setheap (scalar_t__,void*) ; 

void
init_heap(void)
{
	bzero(heap, HEAP_SIZE);

	setheap(heap, (void *)((int)heap + HEAP_SIZE));
}