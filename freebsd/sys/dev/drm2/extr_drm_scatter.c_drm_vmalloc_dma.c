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

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  VM_MEMATTR_WRITE_COMBINING ; 
 int /*<<< orphan*/  kmem_alloc_attr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline vm_offset_t drm_vmalloc_dma(vm_size_t size)
{
	return kmem_alloc_attr(size, M_NOWAIT | M_ZERO, 0,
	    BUS_SPACE_MAXADDR_32BIT, VM_MEMATTR_WRITE_COMBINING);
}