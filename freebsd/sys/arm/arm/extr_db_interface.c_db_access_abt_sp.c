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
 int DB_VAR_GET ; 
 int /*<<< orphan*/  PSR_ABT32_MODE ; 
 int /*<<< orphan*/  get_stackptr (int /*<<< orphan*/ ) ; 

int
db_access_abt_sp(struct db_variable *vp, db_expr_t *valp, int rw)
{

	if (rw == DB_VAR_GET) {
		*valp = get_stackptr(PSR_ABT32_MODE);
		return (1);
	}
	return (0);
}