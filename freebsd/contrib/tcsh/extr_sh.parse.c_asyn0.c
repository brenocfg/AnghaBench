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

/* Variables and functions */
 int /*<<< orphan*/  ERR_TOOMANYRP ; 
 int /*<<< orphan*/  STRand ; 
 int asyn3 (struct wordent*,struct wordent*) ; 
 int asyntax (struct wordent*,struct wordent*) ; 
 int /*<<< orphan*/  eq (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
asyn0(struct wordent *p1, struct wordent *p2)
{
    struct wordent *p;
    int l = 0;

    for (p = p1; p != p2; p = p->next)
	switch (p->word[0]) {

	case '(':
	    l++;
	    continue;

	case ')':
	    l--;
	    if (l < 0)
		stderror(ERR_TOOMANYRP);
	    continue;

	case '>':
	    if (p->next != p2 && eq(p->next->word, STRand))
		p = p->next;
	    continue;

	case '&':
	case '|':
	case ';':
	case '\n':
	    if (l != 0)
		continue;
	    if (asyn3(p1, p) != 0)
		return 1;
	    return asyntax(p->next, p2);

	default:
	    break;
	}
    if (l == 0)
	return asyn3(p1, p2);
    return 0;
}