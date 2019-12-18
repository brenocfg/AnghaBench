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
struct wordent {int* word; struct wordent* next; } ;
struct command {struct command* t_dcdr; struct command* t_dcar; int /*<<< orphan*/  t_dtyp; int /*<<< orphan*/  t_dflg; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_STDERR ; 
 int /*<<< orphan*/  NODE_PIPE ; 
 int P_DIAG ; 
 int P_IN ; 
 int P_OUT ; 
 struct command* syn3 (struct wordent const*,struct wordent const*,int) ; 
 struct command* xcalloc (int,int) ; 

__attribute__((used)) static struct command *
syn2(const struct wordent *p1, const struct wordent *p2, int flags)
{
    const struct wordent *p, *pn;
    struct command *t;
    int l = 0;
    int     f;

    for (p = p1; p != p2; p = p->next)
	switch (p->word[0]) {

	case '(':
	    l++;
	    continue;

	case ')':
	    l--;
	    continue;

	case '|':
	    if (l != 0)
		continue;
	    t = xcalloc(1, sizeof(*t));
	    f = flags | P_OUT;
	    pn = p->next;
	    if (pn != p2 && pn->word[0] == '&') {
		f |= P_DIAG;
		t->t_dflg |= F_STDERR;
	    }
	    t->t_dtyp = NODE_PIPE;
	    t->t_dcar = syn3(p1, p, f);
	    if (pn != p2 && pn->word[0] == '&')
		p = pn;
	    t->t_dcdr = syn2(p->next, p2, flags | P_IN);
	    return (t);

	default:
	    break;
	}
    return (syn3(p1, p2, flags));
}