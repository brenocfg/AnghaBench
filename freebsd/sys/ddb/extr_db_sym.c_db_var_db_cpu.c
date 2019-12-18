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
typedef  int db_expr_t ;

/* Variables and functions */
#define  DB_VAR_GET 129 
#define  DB_VAR_SET 128 
 int db_cpu ; 
 int /*<<< orphan*/  db_printf (char*,...) ; 
 int mp_maxid ; 

int
db_var_db_cpu(struct db_variable *vp, db_expr_t *valuep, int op)
{

	switch (op) {
	case DB_VAR_GET:
		*valuep = db_cpu;
		return (1);

	case DB_VAR_SET:
		if (*(int *)valuep < -1 || *(int *)valuep > mp_maxid) {
			db_printf("Invalid value: %d\n", *(int*)valuep);
			return (0);
		}
		db_cpu = *(int *)valuep;
		return (1);

	default:
		db_printf("db_var_db_cpu: unknown operation\n");
		return (0);
	}
}