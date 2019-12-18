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
struct command {int /*<<< orphan*/  t_dflg; struct command* t_dcdr; struct command* t_dcar; int /*<<< orphan*/  t_dtyp; } ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_OR ; 
 struct command* syn1b (struct wordent const*,struct wordent const*,int) ; 
 struct command* xcalloc (int,int) ; 

__attribute__((used)) static struct command *
syn1a(const struct wordent *p1, const struct wordent *p2, int flags)
{
    const struct wordent *p;
    struct command *t;
    int l = 0;

    for (p = p1; p != p2; p = p->next)
	switch (p->word[0]) {

	case '(':
	    l++;
	    continue;

	case ')':
	    l--;
	    continue;

	case '|':
	    if (p->word[1] != '|')
		continue;
	    if (l == 0) {
		t = xcalloc(1, sizeof(*t));
		t->t_dtyp = NODE_OR;
		t->t_dcar = syn1b(p1, p, flags);
		t->t_dcdr = syn1a(p->next, p2, flags);
		t->t_dflg = 0;
		return (t);
	    }
	    continue;

	default:
	    break;
	}
    return (syn1b(p1, p2, flags));
}