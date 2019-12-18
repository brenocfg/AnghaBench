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
typedef  int /*<<< orphan*/  db_expr_t ;

/* Variables and functions */
 int /*<<< orphan*/  db_printf (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ watch_virt_active () ; 
 int /*<<< orphan*/  watch_virt_get (int*) ; 
 int watch_virt_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
db_md_set_watchpoint(db_expr_t addr, db_expr_t size)
{
	int dummy;

	if (watch_virt_active()) {
		db_printf("Overwriting previously active watch point at "
		    "0x%lx\n", watch_virt_get(&dummy));
	}
	return (watch_virt_set(addr, size));
}