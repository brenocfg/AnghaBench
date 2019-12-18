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

/* Variables and functions */
 int /*<<< orphan*/  db_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  db_logical_and_expr (int*) ; 
 int /*<<< orphan*/  db_printf (char*,char*) ; 
 int db_read_token () ; 
 int /*<<< orphan*/  db_unread_token (int) ; 
 int tLOG_OR ; 

__attribute__((used)) static bool
db_logical_or_expr(
	db_expr_t *valuep)
{
	db_expr_t	lhs, rhs;
	int		t;

	if (!db_logical_and_expr(&lhs))
		return(false);

	t = db_read_token();
	while (t == tLOG_OR) {
		if (!db_logical_and_expr(&rhs)) {
			db_printf("Expression syntax error after '%s'\n", "||");
			db_error(NULL);
			/*NOTREACHED*/
		}
		lhs = (lhs || rhs);
		t = db_read_token();
	}
	db_unread_token(t);
	*valuep = lhs;
	return (true);
}