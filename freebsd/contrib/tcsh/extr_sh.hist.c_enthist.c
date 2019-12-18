#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wordent {TYPE_2__* prev; TYPE_1__* next; } ;
struct Hist {scalar_t__ Htime; int Hnum; int Href; struct wordent Hlex; struct Hist* Hnext; scalar_t__ Hhash; int /*<<< orphan*/ * histline; struct Hist* Hprev; } ;
struct TYPE_6__ {int /*<<< orphan*/  s; } ;
struct TYPE_5__ {struct wordent* next; } ;
struct TYPE_4__ {struct wordent* prev; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 struct Hist Histlist ; 
 scalar_t__ Htime ; 
 int /*<<< orphan*/  const* STRNULL ; 
 int /*<<< orphan*/  STRall ; 
 int /*<<< orphan*/  STRerase ; 
 int /*<<< orphan*/  STRhistdup ; 
 int /*<<< orphan*/  STRprev ; 
 int /*<<< orphan*/ * Strsave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bubbleHnumHrefDown (struct Hist*,struct Hist*) ; 
 int /*<<< orphan*/  copylex (struct wordent*,struct wordent*) ; 
 int /*<<< orphan*/  createHistHashTable (int) ; 
 int /*<<< orphan*/  discardHistHashTable () ; 
 scalar_t__ eq (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eventno ; 
 int /*<<< orphan*/  fastMergeErase ; 
 struct Hist* findHistHashTable (struct wordent*,unsigned int) ; 
 unsigned int hashhist (struct wordent*) ; 
 scalar_t__ heq (struct wordent*,struct wordent*) ; 
 int /*<<< orphan*/  hfree (struct Hist*) ; 
 int /*<<< orphan*/  hinsert (struct Hist*,struct Hist*) ; 
 TYPE_3__ histline ; 
 scalar_t__ histvalid ; 
 int /*<<< orphan*/  hremove (struct Hist*) ; 
 int /*<<< orphan*/  insertHistHashTable (struct Hist*,unsigned int) ; 
 struct Hist* mergeInsertionPoint (struct Hist*,struct Hist*) ; 
 int /*<<< orphan*/  renumberHist (struct Hist*) ; 
 int /*<<< orphan*/  time (scalar_t__*) ; 
 int /*<<< orphan*/ * varval (int /*<<< orphan*/ ) ; 
 struct Hist* xmalloc (int) ; 

struct Hist *
enthist(
  int event,				/* newly incremented global eventno */
  struct wordent *lp,
  int docopy,
  int mflg,				/* true if merge requested */
  int hlen)				/* -1 if unknown */
{
    struct Hist *p = NULL, *pp = &Histlist, *pTime = NULL;
    struct Hist *np;
    const Char *dp;
    unsigned lpHash = 0;                /* non-zero if hashing entries */

    if ((dp = varval(STRhistdup)) != STRNULL) {
	if (eq(dp, STRerase)) {
	    /* masaoki@akebono.tky.hp.com (Kobayashi Masaoki) */
            createHistHashTable(hlen);
            lpHash = hashhist(lp);
            assert(lpHash != 0);
            p = findHistHashTable(lp, lpHash);
            if (p) {
		if (Htime != 0 && p->Htime > Htime)
		    Htime = p->Htime;
                /* If we are merging, and the old entry is at the place we want
                 * to insert the new entry, then remember the place. */
                if (mflg && Htime != 0 && p->Hprev->Htime >= Htime)
                    pTime = p->Hprev;
		if (!fastMergeErase)
		    renumberHist(p);	/* Reset Href of subsequent entries */
                hremove(p);
		hfree(p);
                p = NULL;               /* so new entry is allocated below */
	    }
	}
	else if (eq(dp, STRall)) {
            createHistHashTable(hlen);
            lpHash = hashhist(lp);
            assert(lpHash != 0);
            p = findHistHashTable(lp, lpHash);
	    if (p)   /* p!=NULL, only update this entry's Htime below */
		eventno--;		/* not adding a new event */
	}
	else if (eq(dp, STRprev)) {
	    if (pp->Hnext && heq(lp, &(pp->Hnext->Hlex))) {
		p = pp->Hnext;
		eventno--;
	    }
	}
    }

    np = p ? p : xmalloc(sizeof(*np));

    /* Pick up timestamp set by lex() in Htime if reading saved history */
    if (Htime != 0) {
	np->Htime = Htime;
	Htime = 0;
    }
    else
        (void) time(&(np->Htime));

    if (p == np)
        return np;                      /* reused existing entry */

    /* Initialize the new entry. */
    np->Hnum = np->Href = event;
    if (docopy) {
        copylex(&np->Hlex, lp);
	if (histvalid)
	    np->histline = Strsave(histline.s);
	else
	    np->histline = NULL;
    }
    else {
	np->Hlex.next = lp->next;
	lp->next->prev = &np->Hlex;
	np->Hlex.prev = lp->prev;
        lp->prev->next = &np->Hlex;
        np->histline = NULL;
    }
    np->Hhash = 0;

    /* The head of history list is the default insertion point.
       If merging, advance insertion point, in pp, according to Htime. */
    /* XXX -- In histdup=all, Htime values can be non-monotonic. */
    if (mflg) {                         /* merge according to np->Htime */
        pp = mergeInsertionPoint(np, pTime);
        for (p = pp->Hnext; p && p->Htime == np->Htime; pp = p, p = p->Hnext) {
            if (heq(&p->Hlex, &np->Hlex)) {
                eventno--;              /* duplicate, so don't add new event */
                hfree(np);
                return (p);
              }
          }
        /* pp is now the last entry with time >= to np. */
	if (!fastMergeErase) {		/* renumber at end of loadhist */
	    /* Before inserting np after pp, bubble its Hnum & Href values down
	     * through the earlier part of list. */
	    bubbleHnumHrefDown(np, pp);
	}
    }
    else
        pp = &Histlist;                 /* insert at beginning of history */
    hinsert(np, pp);
    if (lpHash && hlen != 0)		/* erase & all modes use hash table */
        insertHistHashTable(np, lpHash);
    else
        discardHistHashTable();
    return (np);
}