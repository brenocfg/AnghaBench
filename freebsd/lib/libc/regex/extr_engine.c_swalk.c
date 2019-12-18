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
typedef  char wint_t ;
typedef  char uch ;
struct match {char const* offp; char const* beginp; int eflags; char const* endp; char const* coldp; int /*<<< orphan*/  mbs; TYPE_1__* g; int /*<<< orphan*/  tmp; int /*<<< orphan*/  empty; int /*<<< orphan*/  fresh; int /*<<< orphan*/  st; } ;
typedef  int /*<<< orphan*/  states ;
typedef  int /*<<< orphan*/  sopno ;
struct TYPE_2__ {int cflags; int nbol; scalar_t__ neol; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AT (char*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BADCHAR ; 
 char BOL ; 
 char BOLEOL ; 
 char BOW ; 
 int /*<<< orphan*/  CLEAR (int /*<<< orphan*/ ) ; 
 char EOL ; 
 char EOW ; 
 int EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ISWORD (char) ; 
 char NOTHING ; 
 char OUT ; 
 int REG_NEWLINE ; 
 int REG_NOTBOL ; 
 int REG_NOTEOL ; 
 int /*<<< orphan*/  SET1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SP (char*,int /*<<< orphan*/ ,char const) ; 
 int XMBRTOWC (char*,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  step (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char * /* where it ended, or NULL */
walk(struct match *m, const char *start, const char *stop, sopno startst,
	sopno stopst, bool fast)
{
	states st = m->st;
	states fresh = m->fresh;
	states empty = m->empty;
	states tmp = m->tmp;
	const char *p = start;
	wint_t c;
	wint_t lastc;		/* previous c */
	wint_t flagch;
	int i;
	const char *matchp;	/* last p at which a match ended */
	size_t clen;

	AT("slow", start, stop, startst, stopst);
	CLEAR(st);
	SET1(st, startst);
	SP("sstart", st, *p);
	st = step(m->g, startst, stopst, st, NOTHING, st);
	if (fast)
		ASSIGN(fresh, st);
	matchp = NULL;
	if (start == m->offp || (start == m->beginp && !(m->eflags&REG_NOTBOL)))
		c = OUT;
	else {
		/*
		 * XXX Wrong if the previous character was multi-byte.
		 * Newline never is (in encodings supported by FreeBSD),
		 * so this only breaks the ISWORD tests below.
		 */
		c = (uch)*(start - 1);
	}
	for (;;) {
		/* next character */
		lastc = c;
		if (p == m->endp) {
			c = OUT;
			clen = 0;
		} else
			clen = XMBRTOWC(&c, p, m->endp - p, &m->mbs, BADCHAR);

		if (fast && EQ(st, fresh))
			matchp = p;

		/* is there an EOL and/or BOL between lastc and c? */
		flagch = '\0';
		i = 0;
		if ( (lastc == '\n' && m->g->cflags&REG_NEWLINE) ||
				(lastc == OUT && !(m->eflags&REG_NOTBOL)) ) {
			flagch = BOL;
			i = m->g->nbol;
		}
		if ( (c == '\n' && m->g->cflags&REG_NEWLINE) ||
				(c == OUT && !(m->eflags&REG_NOTEOL)) ) {
			flagch = (flagch == BOL) ? BOLEOL : EOL;
			i += m->g->neol;
		}
		if (i != 0) {
			for (; i > 0; i--)
				st = step(m->g, startst, stopst, st, flagch, st);
			SP("sboleol", st, c);
		}

		/* how about a word boundary? */
		if ( (flagch == BOL || (lastc != OUT && !ISWORD(lastc))) &&
					(c != OUT && ISWORD(c)) ) {
			flagch = BOW;
		}
		if ( (lastc != OUT && ISWORD(lastc)) &&
				(flagch == EOL || (c != OUT && !ISWORD(c))) ) {
			flagch = EOW;
		}
		if (flagch == BOW || flagch == EOW) {
			st = step(m->g, startst, stopst, st, flagch, st);
			SP("sboweow", st, c);
		}

		/* are we done? */
		if (ISSET(st, stopst)) {
			if (fast)
				break;
			else
				matchp = p;
		}
		if (EQ(st, empty) || p == stop || clen > (size_t)(stop - p))
			break;		/* NOTE BREAK OUT */

		/* no, we must deal with this character */
		ASSIGN(tmp, st);
		if (fast)
			ASSIGN(st, fresh);
		else
			ASSIGN(st, empty);
		assert(c != OUT);
		st = step(m->g, startst, stopst, tmp, c, st);
		SP("saft", st, c);
		assert(EQ(step(m->g, startst, stopst, st, NOTHING, st), st));
		p += clen;
	}

	if (fast) {
		assert(matchp != NULL);
		m->coldp = matchp;
		if (ISSET(st, stopst))
			return (p + XMBRTOWC(NULL, p, stop - p, &m->mbs, 0));
		else
			return (NULL);
	} else
		return (matchp);
}