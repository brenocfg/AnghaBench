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
typedef  int vm_size_t ;
typedef  scalar_t__ db_expr_t ;

/* Variables and functions */
 scalar_t__ db_expression (scalar_t__*) ; 
 int /*<<< orphan*/  db_map_addr (scalar_t__) ; 
 int /*<<< orphan*/  db_set_watchpoint (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  db_skip_to_eol () ; 

void
db_watchpoint_cmd(db_expr_t addr, bool have_addr, db_expr_t count,
   char *modif)
{
	vm_size_t	size;
	db_expr_t	value;

	if (db_expression(&value))
	    size = (vm_size_t) value;
	else
	    size = 4;
	db_skip_to_eol();

	db_set_watchpoint(db_map_addr(addr), addr, size);
}