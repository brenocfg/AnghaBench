#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ phys_addr; } ;
typedef  TYPE_1__ efi_memory_desc_t ;

/* Variables and functions */

__attribute__((used)) static int cmp_mem_desc(const void *l, const void *r)
{
	const efi_memory_desc_t *left = l, *right = r;

	return (left->phys_addr > right->phys_addr) ? 1 : -1;
}