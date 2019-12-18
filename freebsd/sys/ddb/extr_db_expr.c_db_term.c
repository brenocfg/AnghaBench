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
typedef  scalar_t__ db_expr_t ;

/* Variables and functions */
 scalar_t__ db_dot ; 
 int /*<<< orphan*/  db_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  db_expression (scalar_t__*) ; 
 int /*<<< orphan*/  db_get_variable (scalar_t__*) ; 
 scalar_t__ db_last_addr ; 
 scalar_t__ db_next ; 
 scalar_t__ db_prev ; 
 int /*<<< orphan*/  db_printf (char*,char) ; 
 int db_read_token () ; 
 scalar_t__ db_tok_number ; 
 char db_tok_string ; 
 int /*<<< orphan*/  db_unread_token (int) ; 
 int /*<<< orphan*/  db_value_of_name (char,scalar_t__*) ; 
 int /*<<< orphan*/  db_value_of_name_pcpu (char,scalar_t__*) ; 
 int /*<<< orphan*/  db_value_of_name_vnet (char,scalar_t__*) ; 
 int tDITTO ; 
 int tDOLLAR ; 
 int tDOT ; 
 int tDOTDOT ; 
 int tIDENT ; 
 int tLPAREN ; 
 int tNUMBER ; 
 int tPLUS ; 
 int tRPAREN ; 

__attribute__((used)) static bool
db_term(db_expr_t *valuep)
{
	int	t;

	t = db_read_token();
	if (t == tIDENT) {
	    if (!db_value_of_name(db_tok_string, valuep) &&
		!db_value_of_name_pcpu(db_tok_string, valuep) &&
		!db_value_of_name_vnet(db_tok_string, valuep)) {
		db_printf("Symbol '%s' not found\n", db_tok_string);
		db_error(NULL);
		/*NOTREACHED*/
	    }
	    return (true);
	}
	if (t == tNUMBER) {
	    *valuep = (db_expr_t)db_tok_number;
	    return (true);
	}
	if (t == tDOT) {
	    *valuep = (db_expr_t)db_dot;
	    return (true);
	}
	if (t == tDOTDOT) {
	    *valuep = (db_expr_t)db_prev;
	    return (true);
	}
	if (t == tPLUS) {
	    *valuep = (db_expr_t) db_next;
	    return (true);
	}
	if (t == tDITTO) {
	    *valuep = (db_expr_t)db_last_addr;
	    return (true);
	}
	if (t == tDOLLAR) {
	    if (!db_get_variable(valuep))
		return (false);
	    return (true);
	}
	if (t == tLPAREN) {
	    if (!db_expression(valuep)) {
		db_printf("Expression syntax error after '%c'\n", '(');
		db_error(NULL);
		/*NOTREACHED*/
	    }
	    t = db_read_token();
	    if (t != tRPAREN) {
		db_printf("Expression syntax error -- expected '%c'\n", ')');
		db_error(NULL);
		/*NOTREACHED*/
	    }
	    return (true);
	}
	db_unread_token(t);
	return (false);
}