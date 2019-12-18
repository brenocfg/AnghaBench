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
typedef  char* intmax_t ;
typedef  int db_expr_t ;
typedef  int db_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  db_add_expr (int*) ; 
 int /*<<< orphan*/  db_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  db_printf (char*,char*) ; 
 int db_read_token () ; 
 int /*<<< orphan*/  db_unread_token (int) ; 
 int tSHIFT_L ; 
 int tSHIFT_R ; 

__attribute__((used)) static bool
db_shift_expr(db_expr_t *valuep)
{
	db_expr_t	lhs, rhs;
	int		t;

	if (!db_add_expr(&lhs))
		return (false);
	t = db_read_token();
	while (t == tSHIFT_L || t == tSHIFT_R) {
	    if (!db_add_expr(&rhs)) {
		db_printf("Expression syntax error after '%s'\n",
		    t == tSHIFT_L ? "<<" : ">>");
		db_error(NULL);
		/*NOTREACHED*/
	    }
	    if (rhs < 0) {
		db_printf("Negative shift amount %jd\n", (intmax_t)rhs);
		db_error(NULL);
		/*NOTREACHED*/
	    }
	    if (t == tSHIFT_L)
		lhs <<= rhs;
	    else {
		/* Shift right is unsigned */
		lhs = (db_addr_t)lhs >> rhs;
	    }
	    t = db_read_token();
	}
	db_unread_token(t);
	*valuep = lhs;
	return (true);
}