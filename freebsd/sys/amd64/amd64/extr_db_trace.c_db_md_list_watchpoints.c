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
struct dbreg {int /*<<< orphan*/ * dr; } ;
typedef  int /*<<< orphan*/  db_addr_t ;

/* Variables and functions */
 int DBREG_DR7_ACCESS (int /*<<< orphan*/ ,int) ; 
 scalar_t__ DBREG_DR7_ENABLED (int /*<<< orphan*/ ,int) ; 
 int DBREG_DR7_LEN (int /*<<< orphan*/ ,int) ; 
 int DBREG_DR7_LEN_8 ; 
 scalar_t__ DBREG_DRX (struct dbreg*,int) ; 
 int /*<<< orphan*/  DB_STGY_ANY ; 
 int /*<<< orphan*/  db_printf (char*,...) ; 
 int /*<<< orphan*/  db_printsym (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_dbregs (int /*<<< orphan*/ *,struct dbreg*) ; 
 int /*<<< orphan*/  watchtype_str (int) ; 

void
db_md_list_watchpoints(void)
{
	struct dbreg d;
	int i, len, type;

	fill_dbregs(NULL, &d);

	db_printf("\nhardware watchpoints:\n");
	db_printf("  watch    status        type  len             address\n");
	db_printf("  -----  --------  ----------  ---  ------------------\n");
	for (i = 0; i < 4; i++) {
		if (DBREG_DR7_ENABLED(d.dr[7], i)) {
			type = DBREG_DR7_ACCESS(d.dr[7], i);
			len = DBREG_DR7_LEN(d.dr[7], i);
			if (len == DBREG_DR7_LEN_8)
				len = 8;
			else
				len++;
			db_printf("  %-5d  %-8s  %10s  %3d  ",
			    i, "enabled", watchtype_str(type), len);
			db_printsym((db_addr_t)DBREG_DRX(&d, i), DB_STGY_ANY);
			db_printf("\n");
		} else {
			db_printf("  %-5d  disabled\n", i);
		}
	}

	db_printf("\ndebug register values:\n");
	for (i = 0; i < 8; i++)
		if (i != 4 && i != 5)
			db_printf("  dr%d 0x%016lx\n", i, DBREG_DRX(&d, i));
	db_printf("\n");
}