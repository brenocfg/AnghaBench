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
typedef  int vm_offset_t ;

/* Variables and functions */
 int UMA_SLAB_MASK ; 
 int /*<<< orphan*/ * vtoslab (int) ; 

int
is_vmalloc_addr(const void *addr)
{
	return (vtoslab((vm_offset_t)addr & ~UMA_SLAB_MASK) != NULL);
}