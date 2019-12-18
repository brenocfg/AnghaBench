#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wordent {char* word; struct wordent* prev; struct wordent* next; } ;
typedef  char eChar ;
struct TYPE_3__ {int len; char* s; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_LTOOLONG ; 
 scalar_t__ HISTSUB ; 
 char* STRNULL ; 
 int /*<<< orphan*/  Strbuf_terminate (TYPE_1__*) ; 
 int /*<<< orphan*/  btell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cleanup_ignore (struct wordent*) ; 
 int /*<<< orphan*/  cleanup_push (struct wordent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (struct wordent*) ; 
 int enterhist ; 
 int /*<<< orphan*/  getexcl (char) ; 
 int hadhist ; 
 TYPE_1__ histline ; 
 int histvalid ; 
 scalar_t__ intty ; 
 int /*<<< orphan*/  lex_cleanup ; 
 int /*<<< orphan*/  lineloc ; 
 int /*<<< orphan*/  postcmd_active ; 
 char readc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unreadc (char) ; 
 char* word (int) ; 
 struct wordent* xmalloc (int) ; 

int
lex(struct wordent *hp)
{
    struct wordent *wdp;
    eChar    c;
    int     parsehtime = enterhist;
    int	    toolong = 0;

    histvalid = 0;
    histline.len = 0;

    if (!postcmd_active)
	btell(&lineloc);
    hp->next = hp->prev = hp;
    hp->word = STRNULL;
    hadhist = 0;
    do
	c = readc(0);
    while (c == ' ' || c == '\t');
    if (c == (eChar)HISTSUB && intty)
	/* ^lef^rit	from tty is short !:s^lef^rit */
	getexcl(c);
    else
	unreadc(c);
    cleanup_push(hp, lex_cleanup);
    wdp = hp;
    /*
     * The following loop is written so that the links needed by freelex will
     * be ready and rarin to go even if it is interrupted.
     */
    do {
	struct wordent *new;

	new = xmalloc(sizeof(*new));
	new->word = NULL;
	new->prev = wdp;
	new->next = hp;
	wdp->next = new;
	hp->prev = new;
	wdp = new;
	wdp->word = word(parsehtime);
	parsehtime = 0;
	if (enterhist && toolong++ > 10 * 1024)
	    stderror(ERR_LTOOLONG);
    } while (wdp->word[0] != '\n');
    cleanup_ignore(hp);
    cleanup_until(hp);
    Strbuf_terminate(&histline);
    if (histline.len != 0 && histline.s[histline.len - 1] == '\n')
	histline.s[histline.len - 1] = '\0';
    histvalid = 1;

    return (hadhist);
}