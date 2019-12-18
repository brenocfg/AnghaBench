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
 int /*<<< orphan*/  db_examine (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  db_examine_format ; 
 int /*<<< orphan*/  db_strcpy (int /*<<< orphan*/ ,char*) ; 

void
db_examine_cmd(db_expr_t addr, bool have_addr, db_expr_t count, char *modif)
{
	if (modif[0] != '\0')
	    db_strcpy(db_examine_format, modif);

	if (count == -1)
	    count = 1;

	db_examine((db_addr_t) addr, db_examine_format, count);
}