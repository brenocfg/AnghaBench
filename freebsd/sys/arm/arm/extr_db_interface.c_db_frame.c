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
struct db_variable {scalar_t__ valuep; } ;
typedef  int db_expr_t ;

/* Variables and functions */
 int DB_VAR_GET ; 
 int /*<<< orphan*/ * kdb_frame ; 

int db_frame(struct db_variable *vp, db_expr_t *valp, int rw)
{
	int *reg;

	if (kdb_frame == NULL)
		return (0);

	reg = (int *)((uintptr_t)kdb_frame + (db_expr_t)vp->valuep);
	if (rw == DB_VAR_GET)
		*valp = *reg;
	else
		*reg = *valp;
	return (1);
}