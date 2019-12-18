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
struct varent {int /*<<< orphan*/ * vec; } ;
struct command {int dummy; } ;
typedef  char Char ;

/* Variables and functions */
 int ERR_ASSIGN ; 
 int ERR_NAME ; 
 int ERR_SYNTAX ; 
 int ERR_UNKNOWNOP ; 
 int ERR_VARBEGIN ; 
 char* STR1 ; 
 char* Strsave (char*) ; 
 int /*<<< orphan*/  USE (struct command*) ; 
 int /*<<< orphan*/  VAR_READWRITE ; 
 scalar_t__ alnum (char) ; 
 scalar_t__ any (char*,char) ; 
 int /*<<< orphan*/  asx (char*,int,char*) ; 
 int /*<<< orphan*/  cleanup_ignore (char*) ; 
 int /*<<< orphan*/  cleanup_push (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (char*) ; 
 char* getinx (char*,int*) ; 
 struct varent* getvx (char*,int) ; 
 scalar_t__ letter (char) ; 
 char* operate (char,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  prvars () ; 
 int /*<<< orphan*/  setv (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderror (int) ; 
 int /*<<< orphan*/  update_vars (char*) ; 
 int /*<<< orphan*/  varval (char*) ; 
 int /*<<< orphan*/  xfree ; 
 char* xset (char*,char***) ; 

void
dolet(Char **v, struct command *dummy)
{
    Char *p;
    Char   *vp, c, op;
    int    hadsub;
    int     subscr;

    USE(dummy);
    v++;
    p = *v++;
    if (p == 0) {
	prvars();
	return;
    }
    do {
	hadsub = 0;
	vp = p;
	if (letter(*p))
	    for (; alnum(*p); p++)
		continue;
	if (vp == p || !letter(*vp))
	    stderror(ERR_NAME | ERR_VARBEGIN);
	if (*p == '[') {
	    hadsub++;
	    p = getinx(p, &subscr);
	}
	if (*p == 0 && *v)
	    p = *v++;
	if ((op = *p) != 0)
	    *p++ = 0;
	else
	    stderror(ERR_NAME | ERR_ASSIGN);

	/*
	 * if there is no expression after the '=' then print a "Syntax Error"
	 * message - strike
	 */
	if (*p == '\0' && *v == NULL)
	    stderror(ERR_NAME | ERR_ASSIGN);

	vp = Strsave(vp);
	cleanup_push(vp, xfree);
	if (op == '=') {
	    c = '=';
	    p = xset(p, &v);
	}
	else {
	    c = *p++;
	    if (any("+-", c)) {
		if (c != op || *p)
		    stderror(ERR_NAME | ERR_UNKNOWNOP);
		p = Strsave(STR1);
	    }
	    else {
		if (any("<>", op)) {
		    if (c != op)
			stderror(ERR_NAME | ERR_UNKNOWNOP);
		    stderror(ERR_NAME | ERR_SYNTAX);
		}
		if (c != '=')
		    stderror(ERR_NAME | ERR_UNKNOWNOP);
		p = xset(p, &v);
	    }
	}
	cleanup_push(p, xfree);
	if (op == '=') {
	    if (hadsub)
		asx(vp, subscr, p);
	    else
		setv(vp, p, VAR_READWRITE);
	    cleanup_ignore(p);
	}
	else if (hadsub) {
	    struct varent *gv = getvx(vp, subscr);
	    Char *val;

	    val = operate(op, gv->vec[subscr - 1], p);
	    cleanup_push(val, xfree);
	    asx(vp, subscr, val);
	    cleanup_ignore(val);
	    cleanup_until(val);
	}
	else {
	    Char *val;

	    val = operate(op, varval(vp), p);
	    cleanup_push(val, xfree);
	    setv(vp, val, VAR_READWRITE);
	    cleanup_ignore(val);
	    cleanup_until(val);
	}
	update_vars(vp);
	cleanup_until(vp);
    } while ((p = *v++) != NULL);
}