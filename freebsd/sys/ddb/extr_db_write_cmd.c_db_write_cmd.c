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
typedef  scalar_t__ db_expr_t ;
typedef  void* db_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DB_STGY_ANY ; 
 int /*<<< orphan*/  db_error (char*) ; 
 scalar_t__ db_expression (scalar_t__*) ; 
 scalar_t__ db_get_value (void*,int,int) ; 
 void* db_next ; 
 void* db_prev ; 
 int /*<<< orphan*/  db_printf (char*,long,long) ; 
 int /*<<< orphan*/  db_printsym (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db_put_value (void*,int,scalar_t__) ; 
 int /*<<< orphan*/  db_skip_to_eol () ; 

void
db_write_cmd(db_expr_t address, bool have_addr, db_expr_t count,
    char * modif)
{
	db_addr_t	addr;
	db_expr_t	old_value;
	db_expr_t	new_value;
	int		size;
	bool		wrote_one = false;

	addr = (db_addr_t) address;

	switch (modif[0]) {
	    case 'b':
		size = 1;
		break;
	    case 'h':
		size = 2;
		break;
	    case 'l':
	    case '\0':
		size = 4;
		break;
	    default:
		db_error("Unknown size\n");
		return;
	}

	while (db_expression(&new_value)) {
	    old_value = db_get_value(addr, size, false);
	    db_printsym(addr, DB_STGY_ANY);
	    db_printf("\t\t%#8lr\t=\t%#8lr\n", (long)old_value,(long)new_value);
	    db_put_value(addr, size, new_value);
	    addr += size;

	    wrote_one = true;
	}

	if (!wrote_one)
	    db_error("Nothing written.\n");

	db_next = addr;
	db_prev = addr - size;

	db_skip_to_eol();
}