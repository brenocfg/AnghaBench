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
 int /*<<< orphan*/  db_expression (int*) ; 
 int /*<<< orphan*/  db_flush_lex () ; 
 int /*<<< orphan*/  db_printf (char*) ; 
 int db_read_token () ; 
 int /*<<< orphan*/  db_search (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  db_skip_to_eol () ; 
 int /*<<< orphan*/  db_tok_string ; 
 int /*<<< orphan*/  db_unread_token (int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int tCOMMA ; 
 int tIDENT ; 
 int tSLASH ; 

void
db_search_cmd(db_expr_t dummy1, bool dummy2, db_expr_t dummy3, char *dummy4)
{
	int		t;
	db_addr_t	addr;
	int		size;
	db_expr_t	value;
	db_expr_t	mask;
	db_expr_t	count;

	t = db_read_token();
	if (t == tSLASH) {
	    t = db_read_token();
	    if (t != tIDENT) {
	      bad_modifier:
		db_printf("Bad modifier\n");
		db_flush_lex();
		return;
	    }

	    if (!strcmp(db_tok_string, "b"))
		size = 1;
	    else if (!strcmp(db_tok_string, "h"))
		size = 2;
	    else if (!strcmp(db_tok_string, "l"))
		size = 4;
	    else
		goto bad_modifier;
	} else {
	    db_unread_token(t);
	    size = 4;
	}

	if (!db_expression((db_expr_t *)&addr)) {
	    db_printf("Address missing\n");
	    db_flush_lex();
	    return;
	}

	if (!db_expression(&value)) {
	    db_printf("Value missing\n");
	    db_flush_lex();
	    return;
	}

	if (!db_expression(&mask))
	    mask = 0xffffffffUL;

	t = db_read_token();
	if (t == tCOMMA) {
	    if (!db_expression(&count)) {
		db_printf("Count missing\n");
		db_flush_lex();
		return;
	    }
	} else {
	    db_unread_token(t);
	    count = -1;		/* effectively forever */
	}
	db_skip_to_eol();

	db_search(addr, size, value, mask, count);
}