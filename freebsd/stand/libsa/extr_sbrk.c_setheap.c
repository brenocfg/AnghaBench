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
 uintptr_t MALLOCALIGN_MASK ; 
 void* heapbase ; 
 int maxheap ; 

void
setheap(void *base, void *top)
{
    /* Align start address for the malloc code.  Sigh. */
    heapbase = (void *)(((uintptr_t)base + MALLOCALIGN_MASK) & 
        ~MALLOCALIGN_MASK);
    maxheap = (char *)top - (char *)heapbase;
}