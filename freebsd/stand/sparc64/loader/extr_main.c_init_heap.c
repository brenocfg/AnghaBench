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
typedef  scalar_t__ vm_offset_t ;

/* Variables and functions */
 int /*<<< orphan*/  HEAPSZ ; 
 scalar_t__ HEAPVA ; 
 scalar_t__ OF_claim (void*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ heapva ; 

__attribute__((used)) static vm_offset_t
init_heap(void)
{

	/* There is no need for continuous physical heap memory. */
	heapva = (vm_offset_t)OF_claim((void *)HEAPVA, HEAPSZ, 32);
	return (heapva);
}