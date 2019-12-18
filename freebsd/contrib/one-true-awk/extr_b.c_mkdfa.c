#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uschar ;
typedef  int /*<<< orphan*/  rrow ;
struct TYPE_7__ {int accept; int** posns; int anchor; int /*<<< orphan*/ * restr; int /*<<< orphan*/  initstat; TYPE_1__* re; } ;
typedef  TYPE_2__ fa ;
struct TYPE_6__ {int* lfollow; } ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  ALL ; 
 int /*<<< orphan*/  CAT ; 
 int /*<<< orphan*/  FINAL ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  STAR ; 
 int /*<<< orphan*/ * basestr ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  cfoll (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * firstbasestr ; 
 int /*<<< orphan*/  freetr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  makeinit (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * op2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  overflo (char*) ; 
 int /*<<< orphan*/  penter (int /*<<< orphan*/ *) ; 
 int poscnt ; 
 int /*<<< orphan*/ * reparse (char const*) ; 
 scalar_t__ tostring (char const*) ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ *) ; 

fa *mkdfa(const char *s, int anchor)	/* does the real work of making a dfa */
				/* anchor = 1 for anchored matches, else 0 */
{
	Node *p, *p1;
	fa *f;

	firstbasestr = (uschar *) s;
	basestr = firstbasestr;
	p = reparse(s);
	p1 = op2(CAT, op2(STAR, op2(ALL, NIL, NIL), NIL), p);
		/* put ALL STAR in front of reg.  exp. */
	p1 = op2(CAT, p1, op2(FINAL, NIL, NIL));
		/* put FINAL after reg.  exp. */

	poscnt = 0;
	penter(p1);	/* enter parent pointers and leaf indices */
	if ((f = (fa *) calloc(1, sizeof(fa) + poscnt*sizeof(rrow))) == NULL)
		overflo("out of space for fa");
	f->accept = poscnt-1;	/* penter has computed number of positions in re */
	cfoll(f, p1);	/* set up follow sets */
	freetr(p1);
	if ((f->posns[0] = (int *) calloc(*(f->re[0].lfollow), sizeof(int))) == NULL)
			overflo("out of space in makedfa");
	if ((f->posns[1] = (int *) calloc(1, sizeof(int))) == NULL)
		overflo("out of space in makedfa");
	*f->posns[1] = 0;
	f->initstat = makeinit(f, anchor);
	f->anchor = anchor;
	f->restr = (uschar *) tostring(s);
	if (firstbasestr != basestr) {
		if (basestr)
			xfree(basestr);
	}
	return f;
}