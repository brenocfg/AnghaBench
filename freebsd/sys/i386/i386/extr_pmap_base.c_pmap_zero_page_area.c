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
typedef  int /*<<< orphan*/  vm_page_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* pm_zero_page_area ) (int /*<<< orphan*/ ,int,int) ;} ;

/* Variables and functions */
 TYPE_1__* pmap_methods_ptr ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int) ; 

void
pmap_zero_page_area(vm_page_t m, int off, int size)
{

	pmap_methods_ptr->pm_zero_page_area(m, off, size);
}