#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct match {char const* beginp; char const* endp; int eflags; char const* coldp; TYPE_1__* g; int /*<<< orphan*/  tmp; int /*<<< orphan*/  fresh; int /*<<< orphan*/  st; } ;
typedef  int /*<<< orphan*/  states ;
typedef  int /*<<< orphan*/  sopno ;
struct TYPE_2__ {int cflags; int nbol; scalar_t__ neol; } ;
typedef  char RCHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  ASSIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int BOL ; 
 int BOLEOL ; 
 int BOW ; 
 int /*<<< orphan*/  CLEAR (int /*<<< orphan*/ ) ; 
 int EOL ; 
 int EOW ; 
 int EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ISWORD (char) ; 
 int NOTHING ; 
 char const OUT ; 
 int REG_NEWLINE ; 
 int REG_NOTBOL ; 
 int REG_NOTEOL ; 
 int /*<<< orphan*/  SET1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SP (char*,int /*<<< orphan*/ ,char const) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  step (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const RCHAR_T *			/* where tentative match ended, or NULL */
fast(struct match *m, const RCHAR_T *start, const RCHAR_T *stop, sopno startst,
    sopno stopst)
{
	states st = m->st;
	states fresh = m->fresh;
	states tmp = m->tmp;
	const RCHAR_T *p = start;
	RCHAR_T c = (start == m->beginp) ? OUT : *(start-1);
	RCHAR_T lastc;	/* previous c */
	int flag;
	int i;
	const RCHAR_T *coldp;	/* last p after which no match was underway */

	CLEAR(st);
	SET1(st, startst);
	st = step(m->g, startst, stopst, st, NOTHING, OUT, st);
	ASSIGN(fresh, st);
	SP("start", st, *p);
	coldp = NULL;
	for (;;) {
		/* next character */
		lastc = c;
		c = (p == m->endp) ? OUT : *p;
		if (EQ(st, fresh))
			coldp = p;

		/* is there an EOL and/or BOL between lastc and c? */
		flag = 0;
		i = 0;
		if ( (lastc == '\n' && m->g->cflags&REG_NEWLINE) ||
				(lastc == OUT && !(m->eflags&REG_NOTBOL)) ) {
			flag = BOL;
			i = m->g->nbol;
		}
		if ( (c == '\n' && m->g->cflags&REG_NEWLINE) ||
				(c == OUT && !(m->eflags&REG_NOTEOL)) ) {
			flag = (flag == BOL) ? BOLEOL : EOL;
			i += m->g->neol;
		}
		if (i != 0) {
			for (; i > 0; i--)
				st = step(m->g, startst, stopst, st, flag, OUT, st);
			SP("boleol", st, c);
		}

		/* how about a word boundary? */
		if ( (flag == BOL || (lastc != OUT && !ISWORD(lastc))) &&
					(c != OUT && ISWORD(c)) ) {
			flag = BOW;
		}
		if ( (lastc != OUT && ISWORD(lastc)) &&
				(flag == EOL || (c != OUT && !ISWORD(c))) ) {
			flag = EOW;
		}
		if (flag == BOW || flag == EOW) {
			st = step(m->g, startst, stopst, st, flag, OUT, st);
			SP("boweow", st, c);
		}

		/* are we done? */
		if (ISSET(st, stopst) || p == stop)
			break;		/* NOTE BREAK OUT */

		/* no, we must deal with this character */
		ASSIGN(tmp, st);
		ASSIGN(st, fresh);
		assert(c != OUT);
		st = step(m->g, startst, stopst, tmp, 0, c, st);
		SP("aft", st, c);
		assert(EQ(step(m->g, startst, stopst, st, NOTHING, OUT, st), st));
		p++;
	}

	assert(coldp != NULL);
	m->coldp = coldp;
	if (ISSET(st, stopst))
		return(p+1);
	else
		return(NULL);
}