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
 int /*<<< orphan*/  __unreachable () ; 
 int /*<<< orphan*/  db_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  db_printf (char*,char*) ; 
 int db_read_token () ; 
 int /*<<< orphan*/  db_shift_expr (int*) ; 
 int /*<<< orphan*/  db_unread_token (int) ; 
#define  tGREATER 133 
#define  tGREATER_EQ 132 
#define  tLESS 131 
#define  tLESS_EQ 130 
#define  tLOG_EQ 129 
#define  tLOG_NOT_EQ 128 

__attribute__((used)) static bool
db_logical_relation_expr(
	db_expr_t *valuep)
{
	db_expr_t	lhs, rhs;
	int		t;

	if (!db_shift_expr(&lhs))
	    return (false);

	t = db_read_token();
	while (t == tLOG_EQ || t == tLOG_NOT_EQ || t == tGREATER ||
	    t == tGREATER_EQ || t == tLESS || t == tLESS_EQ) {
	    if (!db_shift_expr(&rhs)) {
		db_printf("Expression syntax error after '%s'\n",
		    t == tLOG_EQ ? "==" : t == tLOG_NOT_EQ ? "!=" :
		    t == tGREATER ? ">" : t == tGREATER_EQ ? ">=" :
		    t == tLESS ? "<" : "<=");
		db_error(NULL);
		/*NOTREACHED*/
	    }
	    switch(t) {
		case tLOG_EQ:
		    lhs = (lhs == rhs);
		    break;
		case tLOG_NOT_EQ:
		    lhs = (lhs != rhs);
		    break;
		case tGREATER:
		    lhs = (lhs > rhs);
		    break;
		case tGREATER_EQ:
		    lhs = (lhs >= rhs);
		    break;
		case tLESS:
		    lhs = (lhs < rhs);
		    break;
		case tLESS_EQ:
		    lhs = (lhs <= rhs);
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