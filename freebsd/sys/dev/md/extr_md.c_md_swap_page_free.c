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
 int /*<<< orphan*/  vm_page_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_xunbusy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
md_swap_page_free(vm_page_t m)
{

	vm_page_xunbusy(m);
	vm_page_free(m);
}