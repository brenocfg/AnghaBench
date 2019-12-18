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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;

/* Variables and functions */
 int /*<<< orphan*/  db_printf (char*) ; 
 int /*<<< orphan*/  db_watch_print (int /*<<< orphan*/ ,int) ; 
 scalar_t__ watch_phys_active () ; 
 int /*<<< orphan*/  watch_phys_get (int*) ; 
 scalar_t__ watch_virt_active () ; 
 int /*<<< orphan*/  watch_virt_get (int*) ; 

void
db_md_list_watchpoints(void)
{
	vm_offset_t va;
	vm_paddr_t pa;
	int bm;

	db_printf("Physical address watchpoint:\n");
	if (watch_phys_active()) {
		pa = watch_phys_get(&bm);
		db_watch_print(pa, bm);
	} else
		db_printf("\tnot active.\n");
	db_printf("Virtual address watchpoint:\n");
	if (watch_virt_active()) {
		va = watch_virt_get(&bm);
		db_watch_print(va, bm);
	} else
		db_printf("\tnot active.\n");
}