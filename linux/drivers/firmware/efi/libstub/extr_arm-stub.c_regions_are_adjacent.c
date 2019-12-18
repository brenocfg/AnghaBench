#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_4__ {scalar_t__ phys_addr; int num_pages; } ;
typedef  TYPE_1__ efi_memory_desc_t ;

/* Variables and functions */
 int EFI_PAGE_SIZE ; 

__attribute__((used)) static bool regions_are_adjacent(efi_memory_desc_t *left,
				 efi_memory_desc_t *right)
{
	u64 left_end;

	if (left == NULL || right == NULL)
		return false;

	left_end = left->phys_addr + left->num_pages * EFI_PAGE_SIZE;

	return left_end == right->phys_addr;
}