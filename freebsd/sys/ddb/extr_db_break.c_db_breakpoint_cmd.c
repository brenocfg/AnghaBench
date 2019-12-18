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
typedef  int db_expr_t ;
typedef  int /*<<< orphan*/  db_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  db_map_addr (int) ; 
 int /*<<< orphan*/  db_set_breakpoint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
db_breakpoint_cmd(db_expr_t addr, bool have_addr, db_expr_t count, char *modif)
{
	if (count == -1)
	    count = 1;

	db_set_breakpoint(db_map_addr(addr), (db_addr_t)addr, count);
}