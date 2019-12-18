#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  db_expr_t ;
struct TYPE_2__ {int /*<<< orphan*/  ds_script; int /*<<< orphan*/  ds_scriptname; } ;

/* Variables and functions */
 int DB_MAXSCRIPTS ; 
 int /*<<< orphan*/  db_printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* db_script_table ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

void
db_scripts_cmd(db_expr_t addr, bool have_addr, db_expr_t count,
    char *modif)
{
	int i;

	for (i = 0; i < DB_MAXSCRIPTS; i++) {
		if (strlen(db_script_table[i].ds_scriptname) != 0) {
			db_printf("%s=%s\n",
			    db_script_table[i].ds_scriptname,
			    db_script_table[i].ds_script);
		}
	}
}