#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wordent {char* word; struct wordent* next; } ;
struct TYPE_3__ {struct wordent* next; } ;
struct Hist {scalar_t__ Hnum; TYPE_1__ Hlex; struct Hist* Hnext; } ;
struct TYPE_4__ {struct Hist* Hnext; } ;
typedef  char Char ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_NOEVENT ; 
 TYPE_2__ Histlist ; 
 int quesarg ; 
 int /*<<< orphan*/  seterror (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  short2str (char*) ; 

__attribute__((used)) static struct Hist *
findev(Char *cp, int anyarg)
{
    struct Hist *hp;

    for (hp = Histlist.Hnext; hp; hp = hp->Hnext) {
	Char   *dp;
	Char *p, *q;
	struct wordent *lp = hp->Hlex.next;
	int     argno = 0;

	/*
	 * The entries added by alias substitution don't have a newline but do
	 * have a negative event number. Savehist() trims off these entries,
	 * but it happens before alias expansion, too early to delete those
	 * from the previous command.
	 */
	if (hp->Hnum < 0)
	    continue;
	if (lp->word[0] == '\n')
	    continue;
	if (!anyarg) {
	    p = cp;
	    q = lp->word;
	    do
		if (!*p)
		    return (hp);
	    while (*p++ == *q++);
	    continue;
	}
	do {
	    for (dp = lp->word; *dp; dp++) {
		p = cp;
		q = dp;
		do
		    if (!*p) {
			quesarg = argno;
			return (hp);
		    }
		while (*p++ == *q++);
	    }
	    lp = lp->next;
	    argno++;
	} while (lp->word[0] != '\n');
    }
    seterror(ERR_NOEVENT, short2str(cp));
    return (0);
}