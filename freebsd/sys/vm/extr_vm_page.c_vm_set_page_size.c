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
struct TYPE_2__ {int v_page_size; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  panic (char*) ; 
 TYPE_1__ vm_cnt ; 

void
vm_set_page_size(void)
{
	if (vm_cnt.v_page_size == 0)
		vm_cnt.v_page_size = PAGE_SIZE;
	if (((vm_cnt.v_page_size - 1) & vm_cnt.v_page_size) != 0)
		panic("vm_set_page_size: page size not a power of two");
}