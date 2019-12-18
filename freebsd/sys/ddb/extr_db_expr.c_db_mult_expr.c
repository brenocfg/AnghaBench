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
 int /*<<< orphan*/  db_error (char*) ; 
 int /*<<< orphan*/  db_printf (char*,char) ; 
 int db_read_token () ; 
 int /*<<< orphan*/  db_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  db_unary (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  db_unread_token (int) ; 
 int /*<<< orphan*/  roundup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  tBIT_AND 129 
 int tHASH ; 
 int tPCT ; 
 int tSLASH ; 
#define  tSTAR 128 

__attribute__((used)) static bool
db_mult_expr(db_expr_t *valuep)
{
	db_expr_t	lhs, rhs;
	int		t;

	if (!db_unary(&lhs))
	    return (false);

	t = db_read_token();
	while (t == tSTAR || t == tSLASH || t == tPCT || t == tHASH ||
	    t == tBIT_AND ) {
	    if (!db_term(&rhs)) {
		db_printf("Expression syntax error after '%c'\n",
		    t == tSTAR ? '*' : t == tSLASH ? '/' : t == tPCT ? '%' :
		    t == tHASH ? '#' : '&');
		db_error(NULL);
		/*NOTREACHED*/
	    }
	    switch(t)  {
		case tSTAR:
		    lhs *= rhs;
		    break;
		case tBIT_AND:
		    lhs &= rhs;
		    break;
		default:
		    if (rhs == 0) {
			db_error("Division by 0\n");
			/*NOTREACHED*/
		    }
		    if (t == tSLASH)
			lhs /= rhs;
		    else if (t == tPCT)
			lhs %= rhs;
		    else
			lhs = roundup(lhs, rhs);
	    }
	    t = db_read_token();
	}
	db_unread_token(t);
	*valuep = lhs;
	return (true);
}