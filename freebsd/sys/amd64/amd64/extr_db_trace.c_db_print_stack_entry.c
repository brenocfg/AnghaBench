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
typedef  int /*<<< orphan*/  register_t ;
typedef  int /*<<< orphan*/  db_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DB_STGY_PROC ; 
 int /*<<< orphan*/  db_printf (char*,...) ; 
 int /*<<< orphan*/  db_printsym (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
db_print_stack_entry(const char *name, db_addr_t callpc, void *frame)
{

	db_printf("%s() at ", name != NULL ? name : "??");
	db_printsym(callpc, DB_STGY_PROC);
	if (frame != NULL)
		db_printf("/frame 0x%lx", (register_t)frame);
	db_printf("\n");
}