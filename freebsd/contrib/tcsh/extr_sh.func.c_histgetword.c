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
struct wordent {void* word; struct wordent* next; struct wordent* prev; } ;
struct Strbuf {int /*<<< orphan*/ * s; scalar_t__ len; scalar_t__ size; } ;
typedef  char eChar ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 char CHAR_ERR ; 
 int ERR_NAME ; 
 int ERR_NOTFOUND ; 
 int /*<<< orphan*/  Sgoal ; 
 int /*<<< orphan*/  Strbuf_append1 (struct Strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Strbuf_terminate (struct Strbuf*) ; 
 void* Strsave (int /*<<< orphan*/ *) ; 
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
 void* xmalloc (int) ; 

__attribute__((used)) static struct wordent *
histgetword(struct wordent *histent) 
{
    int first;
    eChar c, d;
    int e;
    struct Strbuf *tmp;
    tmp = xmalloc(sizeof(*tmp));
    tmp->size = 0;
    tmp->s = NULL;
    c = readc(1);
    d = 0;
    e = 0;
    for (;;) {
	tmp->len = 0;
	Strbuf_terminate (tmp);
	while (c == ' ' || c == '\t')
	    c = readc(1);
	if (c == '#')
	    do
		c = readc(1);
	    while (c != CHAR_ERR && c != '\n');
	if (c == CHAR_ERR)
	    goto past;
	if (c == '\n') 
	    goto nl;
	unreadc(c);
	first = 1;
	do {
	    e = (c == '\\');
	    c = readc(1);
	    if (c == '\\' && !e) {
		if ((c = readc(1)) == '\n') {
		    e = 1;
		    c = ' ';
		} else {
		    unreadc(c);
		    c = '\\';
		}
	    }
	    if ((c == '\'' || c == '"') && !e) {
		if (d == 0)
		    d = c;
		else if (d == c)
		    d = 0;
	    }
	    if (c == CHAR_ERR)
		goto past;
	    
	    Strbuf_append1(tmp, (Char) c);
	    
	    if (!first && !d && c == '(' && !e) {
		break;
	    }
	    first = 0;
	} while (d || e || (c != ' ' && c != '\t' && c != '\n'));
	tmp->len--;
	if (tmp->len) {
	    Strbuf_terminate(tmp);
	    histent->word = Strsave(tmp->s);
	    histent->next = xmalloc(sizeof (*histent));
	    histent->next->prev = histent;
	    histent = histent->next;
	}
	if (c == '\n') {
	nl:
	    tmp->len = 0;
	    Strbuf_append1(tmp, (Char) c);
	    Strbuf_terminate(tmp);
	    histent->word = Strsave(tmp->s);
	    return histent;
	}
    }
    
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
    return NULL;
}