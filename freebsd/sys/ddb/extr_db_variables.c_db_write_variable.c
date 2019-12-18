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
struct db_variable {int (* fcn ) (struct db_variable*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * valuep; } ;
typedef  int (* db_varfcn_t ) (struct db_variable*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  db_expr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DB_VAR_SET ; 
 int FCN_NULL (struct db_variable*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (struct db_variable*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
db_write_variable(struct db_variable *vp, db_expr_t value)
{
	db_varfcn_t *func = vp->fcn;

	if (func == FCN_NULL) {
		*(vp->valuep) = value;
		return (1);
	}
	return ((*func)(vp, &value, DB_VAR_SET));
}