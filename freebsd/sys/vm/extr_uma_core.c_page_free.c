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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int uint8_t ;

/* Variables and functions */
 int UMA_SLAB_KERNEL ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int) ; 

__attribute__((used)) static void
page_free(void *mem, vm_size_t size, uint8_t flags)
{

	if ((flags & UMA_SLAB_KERNEL) == 0)
		panic("UMA: page_free used with invalid flags %x", flags);

	kmem_free((vm_offset_t)mem, size);
}