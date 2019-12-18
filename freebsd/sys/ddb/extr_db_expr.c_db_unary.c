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
typedef  int /*<<< orphan*/  db_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  db_error (int /*<<< orphan*/ *) ; 
 int db_get_value (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  db_printf (char*,char) ; 
 int db_read_token () ; 
 int db_term (int*) ; 
 int /*<<< orphan*/  db_unread_token (int) ; 
 int tBIT_NOT ; 
 int tEXCL ; 
 int tMINUS ; 
 int tSTAR ; 

__attribute__((used)) static bool
db_unary(db_expr_t *valuep)
{
	int	t;

	t = db_read_token();
	if (t == tMINUS) {
	    if (!db_unary(valuep)) {
		db_printf("Expression syntax error after '%c'\n", '-');
		db_error(NULL);
		/*NOTREACHED*/
	    }
	    *valuep = -*valuep;
	    return (true);
	}
	if (t == tEXCL) {
	    if(!db_unary(valuep)) {
		db_printf("Expression syntax error after '%c'\n", '!');
		db_error(NULL);
		/* NOTREACHED  */
	    }
	    *valuep = (!(*valuep));
	    return (true);
	}
	if (t == tBIT_NOT) {
	    if(!db_unary(valuep)) {
		db_printf("Expression syntax error after '%c'\n", '~');
		db_error(NULL);
		/* NOTREACHED */
	    }
	    *valuep = (~(*valuep));
	    return (true);
	}
	if (t == tSTAR) {
	    /* indirection */
	    if (!db_unary(valuep)) {
		db_printf("Expression syntax error after '%c'\n", '*');
		db_error(NULL);
		/*NOTREACHED*/
	    }
	    *valuep = db_get_value((db_addr_t)*valuep, sizeof(void *),
		false);
	    return (true);
	}
	db_unread_token(t);
	return (db_term(valuep));
}