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
struct Strbuf {int len; } ;
typedef  char eChar ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 char CHAR_ERR ; 
 int ERR_NAME ; 
 int ERR_NOTFOUND ; 
 int /*<<< orphan*/  Sgoal ; 
 int /*<<< orphan*/  Strbuf_append1 (struct Strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Strbuf_terminate (struct Strbuf*) ; 
 int Stype ; 
#define  TC_BREAK 133 
#define  TC_BRKSW 132 
#define  TC_ELSE 131 
#define  TC_GOTO 130 
#define  TC_IF 129 
#define  TC_SWITCH 128 
 char readc (int) ; 
 int /*<<< orphan*/  setname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  short2str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderror (int,char*) ; 
 int /*<<< orphan*/  unreadc (char) ; 

__attribute__((used)) static int
getword(struct Strbuf *wp)
{
    int found = 0, first;
    eChar c, d;

    if (wp)
	wp->len = 0;
    c = readc(1);
    d = 0;
    do {
	while (c == ' ' || c == '\t')
	    c = readc(1);
	if (c == '#')
	    do
		c = readc(1);
	    while (c != CHAR_ERR && c != '\n');
	if (c == CHAR_ERR)
	    goto past;
	if (c == '\n') {
	    if (wp)
		break;
	    return (0);
	}
	unreadc(c);
	found = 1;
	first = 1;
	do {
	    c = readc(1);
	    if (c == '\\' && (c = readc(1)) == '\n')
		c = ' ';
	    if (c == '\'' || c == '"') {
		if (d == 0)
		    d = c;
		else if (d == c)
		    d = 0;
	    }
	    if (c == CHAR_ERR)
		goto past;
	    if (wp)
		Strbuf_append1(wp, (Char) c);
	    if (!d && c == ')') {
		if (!first && wp) {
		    goto past_word_end;
		} else {
		    if (wp) {
			wp->len = 1;
			Strbuf_terminate(wp);
		    }
		    return found;
		}
	    }
	    if (!first && !d && c == '(') {
		if (wp)
		    goto past_word_end;
		else 
		    break;
	    }
	    first = 0;
	} while ((d || (c != ' ' && c != '\t')) && c != '\n');
    } while (wp == 0);

 past_word_end:
    unreadc(c);
    if (found) {
	wp->len--;
	Strbuf_terminate(wp);
    }

    return (found);

past:
    switch (Stype) {

    case TC_IF:
	stderror(ERR_NAME | ERR_NOTFOUND, "then/endif");
	break;

    case TC_ELSE:
	stderror(ERR_NAME | ERR_NOTFOUND, "endif");
	break;

    case TC_BRKSW:
    case TC_SWITCH:
	stderror(ERR_NAME | ERR_NOTFOUND, "endsw");
	break;

    case TC_BREAK:
	stderror(ERR_NAME | ERR_NOTFOUND, "end");
	break;

    case TC_GOTO:
	setname(short2str(Sgoal));
	stderror(ERR_NAME | ERR_NOTFOUND, "label");
	break;

    default:
	break;
    }
    /* NOTREACHED */
    return (0);
}