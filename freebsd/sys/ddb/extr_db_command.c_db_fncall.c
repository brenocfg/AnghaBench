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
 scalar_t__ DB_CALL (scalar_t__,scalar_t__*,int,scalar_t__*) ; 
 int DB_MAXARGS ; 
 int /*<<< orphan*/  db_disable_pager () ; 
 scalar_t__ db_expression (scalar_t__*) ; 
 int /*<<< orphan*/  db_flush_lex () ; 
 int /*<<< orphan*/  db_printf (char*,...) ; 
 int db_read_token () ; 
 int /*<<< orphan*/  db_skip_to_eol () ; 
 int /*<<< orphan*/  db_unread_token (int) ; 
 int tCOMMA ; 
 int tLPAREN ; 
 int tRPAREN ; 

__attribute__((used)) static void
db_fncall(db_expr_t dummy1, bool dummy2, db_expr_t dummy3, char *dummy4)
{
	db_expr_t	fn_addr;
	db_expr_t	args[DB_MAXARGS];
	int		nargs = 0;
	db_expr_t	retval;
	int		t;

	if (!db_expression(&fn_addr)) {
	    db_printf("Bad function\n");
	    db_flush_lex();
	    return;
	}

	t = db_read_token();
	if (t == tLPAREN) {
	    if (db_expression(&args[0])) {
		nargs++;
		while ((t = db_read_token()) == tCOMMA) {
		    if (nargs == DB_MAXARGS) {
			db_printf("Too many arguments (max %d)\n", DB_MAXARGS);
			db_flush_lex();
			return;
		    }
		    if (!db_expression(&args[nargs])) {
			db_printf("Argument missing\n");
			db_flush_lex();
			return;
		    }
		    nargs++;
		}
		db_unread_token(t);
	    }
	    if (db_read_token() != tRPAREN) {
	        db_printf("Mismatched parens\n");
		db_flush_lex();
		return;
	    }
	}
	db_skip_to_eol();
	db_disable_pager();

	if (DB_CALL(fn_addr, &retval, nargs, args))
		db_printf("= %#lr\n", (long)retval);
}