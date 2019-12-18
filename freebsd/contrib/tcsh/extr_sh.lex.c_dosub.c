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
struct wordent {struct wordent* prev; int /*<<< orphan*/ * word; struct wordent* next; } ;
struct Hist {struct wordent Hlex; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_MODFAIL ; 
 int FLAG_A ; 
 int FLAG_G ; 
 int /*<<< orphan*/  HIST_PURGE ; 
 int /*<<< orphan*/ * STRNULL ; 
 scalar_t__ Strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Strsave (int /*<<< orphan*/ *) ; 
 struct Hist* enthist (int /*<<< orphan*/ ,struct wordent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int exclc ; 
 int /*<<< orphan*/  seterror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * subword (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,size_t*) ; 
 struct wordent* xcalloc (int,int) ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct wordent *
dosub(Char sc, struct wordent *en, int global)
{
    struct wordent lexi;
    int    didsub = 0, didone = 0;
    struct wordent *hp = &lexi;
    struct wordent *wdp;
    int i = exclc;
    struct Hist *hst;

    wdp = hp;
    while (--i >= 0) {
	struct wordent *new = xcalloc(1, sizeof *wdp);

	new->word = 0;
	new->prev = wdp;
	new->next = hp;
	wdp->next = new;
	wdp = new;
	en = en->next;
	if (en->word) {
	    Char *tword, *otword;

	    if ((global & FLAG_G) || didsub == 0) {
		size_t pos;

		pos = 0;
		tword = subword(en->word, sc, &didone, &pos);
		if (didone)
		    didsub = 1;
		if (global & FLAG_A) {
		    while (didone && tword != STRNULL) {
			otword = tword;
			tword = subword(otword, sc, &didone, &pos);
			if (Strcmp(tword, otword) == 0) {
			    xfree(otword);
			    break;
			}
			else
			    xfree(otword);
		    }
		}
	    }
	    else
		tword = Strsave(en->word);
	    wdp->word = tword;
	}
    }
    if (didsub == 0)
	seterror(ERR_MODFAIL);
    hp->prev = wdp;
    /* 
     * ANSI mode HP/UX compiler chokes on
     * return &enthist(HIST_PURGE, &lexi, 0)->Hlex;
     */
    hst = enthist(HIST_PURGE, &lexi, 0, 0, -1);
    return &(hst->Hlex);
}