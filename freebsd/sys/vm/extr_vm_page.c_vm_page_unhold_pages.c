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
 int /*<<< orphan*/  PQ_ACTIVE ; 
 int /*<<< orphan*/  vm_page_unwire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
vm_page_unhold_pages(vm_page_t *ma, int count)
{

	for (; count != 0; count--) {
		vm_page_unwire(*ma, PQ_ACTIVE);
		ma++;
	}
}