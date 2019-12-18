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
struct db_variable {int dummy; } ;
typedef  int /*<<< orphan*/  db_expr_t ;

/* Variables and functions */
 int /*<<< orphan*/  db_find_variable (struct db_variable**) ; 
 int db_write_variable (struct db_variable*,int /*<<< orphan*/ ) ; 

int
db_set_variable(db_expr_t value)
{
	struct db_variable *vp;

	if (!db_find_variable(&vp))
		return (0);

	return (db_write_variable(vp, value));
}