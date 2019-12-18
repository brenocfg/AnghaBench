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
typedef  char db_expr_t ;
typedef  int db_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DB_STGY_ANY ; 
 int db_disasm (int,int) ; 
 int /*<<< orphan*/  db_end_line (int) ; 
 char db_get_value (int,int,int) ; 
 int db_next ; 
 int /*<<< orphan*/  db_pager_quit ; 
 int db_prev ; 
 int /*<<< orphan*/  db_print_position () ; 
 int /*<<< orphan*/  db_printf (char*,...) ; 
 int /*<<< orphan*/  db_printsym (char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
db_examine(db_addr_t addr, char *fmt, int count)
{
	int		c;
	db_expr_t	value;
	int		size;
	int		width;
	char *		fp;

	while (--count >= 0 && !db_pager_quit) {
	    fp = fmt;
	    size = 4;
	    while ((c = *fp++) != 0) {
		switch (c) {
		    case 'b':
			size = 1;
			break;
		    case 'h':
			size = 2;
			break;
		    case 'l':
			size = 4;
			break;
		    case 'g':
			size = 8;
			break;
		    case 'a':	/* address */
			size = sizeof(void *);
			/* always forces a new line */
			if (db_print_position() != 0)
			    db_printf("\n");
			db_prev = addr;
			db_printsym(addr, DB_STGY_ANY);
			db_printf(":\t");
			break;
		    default:
			if (db_print_position() == 0) {
			    /* Print the address. */
			    db_printsym(addr, DB_STGY_ANY);
			    db_printf(":\t");
			    db_prev = addr;
			}

			width = size * 4;
			switch (c) {
			    case 'r':	/* signed, current radix */
				value = db_get_value(addr, size, true);
				addr += size;
				db_printf("%+-*lr", width, (long)value);
				break;
			    case 'x':	/* unsigned hex */
				value = db_get_value(addr, size, false);
				addr += size;
				db_printf("%-*lx", width, (long)value);
				break;
			    case 'z':	/* signed hex */
				value = db_get_value(addr, size, true);
				addr += size;
				db_printf("%-*ly", width, (long)value);
				break;
			    case 'd':	/* signed decimal */
				value = db_get_value(addr, size, true);
				addr += size;
				db_printf("%-*ld", width, (long)value);
				break;
			    case 'u':	/* unsigned decimal */
				value = db_get_value(addr, size, false);
				addr += size;
				db_printf("%-*lu", width, (long)value);
				break;
			    case 'o':	/* unsigned octal */
				value = db_get_value(addr, size, false);
				addr += size;
				db_printf("%-*lo", width, (long)value);
				break;
			    case 'c':	/* character */
				value = db_get_value(addr, 1, false);
				addr += 1;
				if (value >= ' ' && value <= '~')
				    db_printf("%c", (int)value);
				else
				    db_printf("\\%03o", (int)value);
				break;
			    case 's':	/* null-terminated string */
				for (;;) {
				    value = db_get_value(addr, 1, false);
				    addr += 1;
				    if (value == 0)
					break;
				    if (value >= ' ' && value <= '~')
					db_printf("%c", (int)value);
				    else
					db_printf("\\%03o", (int)value);
				}
				break;
			    case 'S':	/* symbol */
				value = db_get_value(addr, sizeof(void *),
				    false);
				addr += sizeof(void *);
				db_printsym(value, DB_STGY_ANY);
				break;
			    case 'i':	/* instruction */
				addr = db_disasm(addr, false);
				break;
			    case 'I':	/* instruction, alternate form */
				addr = db_disasm(addr, true);
				break;
			    default:
				break;
			}
			if (db_print_position() != 0)
			    db_end_line(1);
			break;
		}
	    }
	}
	db_next = addr;
}