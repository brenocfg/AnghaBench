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
typedef  int /*<<< orphan*/  db_expr_t ;

/* Variables and functions */
 int /*<<< orphan*/  __unreachable () ; 
 int /*<<< orphan*/  db_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  db_mult_expr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  db_printf (char*,char) ; 
 int db_read_token () ; 
 int /*<<< orphan*/  db_unread_token (int) ; 
#define  tBIT_OR 130 
#define  tMINUS 129 
#define  tPLUS 128 

__attribute__((used)) static bool
db_add_expr(db_expr_t *valuep)
{
	db_expr_t	lhs, rhs;
	int		t;

	if (!db_mult_expr(&lhs))
	    return (false);

	t = db_read_token();
	while (t == tPLUS || t == tMINUS || t == tBIT_OR) {
	    if (!db_mult_expr(&rhs)) {
		db_printf("Expression syntax error after '%c'\n",
		    t == tPLUS ? '+' : t == tMINUS ? '-' : '|');
		db_error(NULL);
		/*NOTREACHED*/
	    }
	    switch (t) {
	    case tPLUS:
		lhs += rhs;
		break;
	    case tMINUS:
		lhs -= rhs;
		break;
	    case tBIT_OR:
		lhs |= rhs;
		break;
	    default:
		__unreachable();
	    }
	    t = db_read_token();
	}
	db_unread_token(t);
	*valuep = lhs;
	return (true);
}