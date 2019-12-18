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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct malloc_type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  malloc_type_freed (struct malloc_type*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_page (unsigned long) ; 

void
contigfree(void *addr, unsigned long size, struct malloc_type *type)
{

	kmem_free((vm_offset_t)addr, size);
	malloc_type_freed(type, round_page(size));
}