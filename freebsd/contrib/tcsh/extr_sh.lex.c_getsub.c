#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct wordent {int dummy; } ;
typedef  char eChar ;
struct TYPE_7__ {scalar_t__ len; int /*<<< orphan*/ * s; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_BADBANGMOD ; 
 int /*<<< orphan*/  ERR_BADSUBST ; 
 int /*<<< orphan*/  ERR_LHS ; 
 int /*<<< orphan*/  ERR_NOSUBST ; 
 int FLAG_A ; 
 int FLAG_G ; 
 int /*<<< orphan*/  Isdigit (char) ; 
 int /*<<< orphan*/  Strbuf_append (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Strbuf_append1 (TYPE_1__*,char) ; 
 int /*<<< orphan*/  Strbuf_terminate (TYPE_1__*) ; 
 scalar_t__ Strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  any (char*,char) ; 
 struct wordent* dosub (char,struct wordent*,int) ; 
 scalar_t__ exclc ; 
 scalar_t__ exclnxt ; 
 char getC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  justpr ; 
 int /*<<< orphan*/  letter (char) ; 
 TYPE_1__ lhsb ; 
 TYPE_1__ rhsb ; 
 int /*<<< orphan*/  seterror (int /*<<< orphan*/ ,...) ; 
 TYPE_1__ slhs ; 
 int /*<<< orphan*/  unreadc (char) ; 

__attribute__((used)) static struct wordent *
getsub(struct wordent *en)
{
    eChar   delim;
    eChar   c;
    eChar   sc;
    int global;

    do {
	exclnxt = 0;
	global = 0;
	sc = c = getC(0);
	while (c == 'g' || c == 'a') {
	    global |= (c == 'g') ? FLAG_G : FLAG_A;
	    sc = c = getC(0);
	}

	switch (c) {
	case 'p':
	    justpr++;
	    return (en);

	case 'x':
	case 'q':
	    global |= FLAG_G;
	    /*FALLTHROUGH*/

	case 'h':
	case 'r':
	case 't':
	case 'e':
	case 'u':
	case 'l':
	    break;

	case '&':
	    if (slhs.len == 0) {
		seterror(ERR_NOSUBST);
		return (en);
	    }
	    lhsb.len = 0;
	    Strbuf_append(&lhsb, slhs.s);
	    Strbuf_terminate(&lhsb);
	    break;

#ifdef notdef
	case '~':
	    if (lhsb.len == 0)
		goto badlhs;
	    break;
#endif

	case 's':
	    delim = getC(0);
	    if (letter(delim) || Isdigit(delim) || any(" \t\n", delim)) {
		unreadc(delim);
		lhsb.len = 0;
		seterror(ERR_BADSUBST);
		return (en);
	    }
	    Strbuf_terminate(&lhsb);
	    lhsb.len = 0;
	    for (;;) {
		c = getC(0);
		if (c == '\n') {
		    unreadc(c);
		    break;
		}
		if (c == delim)
		    break;
		if (c == '\\') {
		    c = getC(0);
		    if (c != delim && c != '\\')
			Strbuf_append1(&lhsb, '\\');
		}
		Strbuf_append1(&lhsb, c);
	    }
	    if (lhsb.len != 0)
		Strbuf_terminate(&lhsb);
	    else if (lhsb.s[0] == 0) {
		seterror(ERR_LHS);
		return (en);
	    } else
		lhsb.len = Strlen(lhsb.s); /* lhsb.s wasn't changed */
	    rhsb.len = 0;
	    for (;;) {
		c = getC(0);
		if (c == '\n') {
		    unreadc(c);
		    break;
		}
		if (c == delim)
		    break;
		if (c == '\\') {
		    c = getC(0);
		    if (c != delim /* && c != '~' */ )
			Strbuf_append1(&rhsb,  '\\');
		}
		Strbuf_append1(&rhsb, c);
	    }
	    Strbuf_terminate(&rhsb);
	    break;

	default:
	    if (c == '\n')
		unreadc(c);
	    seterror(ERR_BADBANGMOD, (int)c);
	    return (en);
	}
	slhs.len = 0;
	if (lhsb.s != NULL && lhsb.len != 0)
	    Strbuf_append(&slhs, lhsb.s);
	Strbuf_terminate(&slhs);
	if (exclc)
	    en = dosub(sc, en, global);
    }
    while ((c = getC(0)) == ':');
    unreadc(c);
    return (en);
}