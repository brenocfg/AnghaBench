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
typedef  int /*<<< orphan*/  vm_page_t ;

/* Variables and functions */
 int /*<<< orphan*/  vm_page_bits (int,int) ; 
 int /*<<< orphan*/  vm_page_clear_dirty_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
vm_page_clear_dirty(vm_page_t m, int base, int size)
{

	vm_page_clear_dirty_mask(m, vm_page_bits(base, size));
}