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
 int /*<<< orphan*/  DB_STGY_ANY ; 
 int /*<<< orphan*/  db_error (char*) ; 
 char db_print_format ; 
 int /*<<< orphan*/  db_printf (char*,...) ; 
 int /*<<< orphan*/  db_printsym (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
db_print_cmd(db_expr_t addr, bool have_addr, db_expr_t count, char *modif)
{
	db_expr_t	value;

	if (modif[0] != '\0')
	    db_print_format = modif[0];

	switch (db_print_format) {
	    case 'a':
		db_printsym((db_addr_t)addr, DB_STGY_ANY);
		break;
	    case 'r':
		db_printf("%+11lr", (long)addr);
		break;
	    case 'x':
		db_printf("%8lx", (unsigned long)addr);
		break;
	    case 'z':
		db_printf("%8ly", (long)addr);
		break;
	    case 'd':
		db_printf("%11ld", (long)addr);
		break;
	    case 'u':
		db_printf("%11lu", (unsigned long)addr);
		break;
	    case 'o':
		db_printf("%16lo", (unsigned long)addr);
		break;
	    case 'c':
		value = addr & 0xFF;
		if (value >= ' ' && value <= '~')
		    db_printf("%c", (int)value);
		else
		    db_printf("\\%03o", (int)value);
		break;
	    default:
		db_print_format = 'x';
		db_error("Syntax error: unsupported print modifier\n");
		/*NOTREACHED*/
	}
	db_printf("\n");
}