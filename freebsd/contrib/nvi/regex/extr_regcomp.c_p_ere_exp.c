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
struct parse {TYPE_1__* g; void** pend; void** pbegin; } ;
typedef  size_t sopno ;
typedef  int /*<<< orphan*/  UCHAR_T ;
struct TYPE_2__ {size_t nsub; int cflags; int /*<<< orphan*/  neol; int /*<<< orphan*/  iflags; int /*<<< orphan*/  nbol; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHEAD (size_t) ; 
 int /*<<< orphan*/  ASTERN (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  EAT (char) ; 
 int /*<<< orphan*/  EMIT (int /*<<< orphan*/ ,size_t) ; 
 char GETNEXT () ; 
 void* HERE () ; 
 int INFINITY ; 
 int /*<<< orphan*/  INSERT (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ ISDIGIT (int /*<<< orphan*/ ) ; 
 int MORE () ; 
 scalar_t__ MORE2 () ; 
 int /*<<< orphan*/  MUSTEAT (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEXT () ; 
 size_t NPAREN ; 
 int /*<<< orphan*/  OANY ; 
 int /*<<< orphan*/  OBOL ; 
 int /*<<< orphan*/  OCH_ ; 
 int /*<<< orphan*/  OEOL ; 
 int /*<<< orphan*/  OLPAREN ; 
 int /*<<< orphan*/  OOR1 ; 
 int /*<<< orphan*/  OOR2 ; 
 int /*<<< orphan*/  OPLUS_ ; 
 int /*<<< orphan*/  OQUEST_ ; 
 int /*<<< orphan*/  ORPAREN ; 
 int /*<<< orphan*/  O_CH ; 
 int /*<<< orphan*/  O_PLUS ; 
 int /*<<< orphan*/  O_QUEST ; 
 char PEEK () ; 
 scalar_t__ PEEK2 () ; 
 int /*<<< orphan*/  REG_BADBR ; 
 int /*<<< orphan*/  REG_BADRPT ; 
 int /*<<< orphan*/  REG_EBRACE ; 
 int /*<<< orphan*/  REG_EESCAPE ; 
 int /*<<< orphan*/  REG_EMPTY ; 
 int /*<<< orphan*/  REG_EPAREN ; 
 int REG_NEWLINE ; 
 int /*<<< orphan*/  REQUIRE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEE (char) ; 
 int /*<<< orphan*/  SETERROR (int /*<<< orphan*/ ) ; 
 size_t THERE () ; 
 size_t THERETHERE () ; 
 int /*<<< orphan*/  USEBOL ; 
 int /*<<< orphan*/  USEEOL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  nonnewline (struct parse*) ; 
 int /*<<< orphan*/  ordinary (struct parse*,char) ; 
 int /*<<< orphan*/  p_bracket (struct parse*) ; 
 int p_count (struct parse*) ; 
 int /*<<< orphan*/  p_ere (struct parse*,char,size_t) ; 
 int /*<<< orphan*/  repeat (struct parse*,size_t,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
p_ere_exp(struct parse *p, size_t reclimit)
{
	char c;
	sopno pos;
	int count;
	int count2;
	sopno subno;
	int wascaret = 0;

	assert(MORE());		/* caller should have ensured this */
	c = GETNEXT();

	pos = HERE();
	switch (c) {
	case '(':
		(void)REQUIRE(MORE(), REG_EPAREN);
		p->g->nsub++;
		subno = p->g->nsub;
		if (subno < NPAREN)
			p->pbegin[subno] = HERE();
		EMIT(OLPAREN, subno);
		if (!SEE(')'))
			p_ere(p, ')', reclimit);
		if (subno < NPAREN) {
			p->pend[subno] = HERE();
			assert(p->pend[subno] != 0);
		}
		EMIT(ORPAREN, subno);
		(void)MUSTEAT(')', REG_EPAREN);
		break;
#ifndef POSIX_MISTAKE
	case ')':		/* happens only if no current unmatched ( */
		/*
		 * You may ask, why the ifndef?  Because I didn't notice
		 * this until slightly too late for 1003.2, and none of the
		 * other 1003.2 regular-expression reviewers noticed it at
		 * all.  So an unmatched ) is legal POSIX, at least until
		 * we can get it fixed.
		 */
		SETERROR(REG_EPAREN);
		break;
#endif
	case '^':
		EMIT(OBOL, 0);
		p->g->iflags |= USEBOL;
		p->g->nbol++;
		wascaret = 1;
		break;
	case '$':
		EMIT(OEOL, 0);
		p->g->iflags |= USEEOL;
		p->g->neol++;
		break;
	case '|':
		SETERROR(REG_EMPTY);
		break;
	case '*':
	case '+':
	case '?':
		SETERROR(REG_BADRPT);
		break;
	case '.':
		if (p->g->cflags&REG_NEWLINE)
			nonnewline(p);
		else
			EMIT(OANY, 0);
		break;
	case '[':
		p_bracket(p);
		break;
	case '\\':
		(void)REQUIRE(MORE(), REG_EESCAPE);
		c = GETNEXT();
		ordinary(p, c);
		break;
	case '{':		/* okay as ordinary except if digit follows */
		(void)REQUIRE(!MORE() || !ISDIGIT((UCHAR_T)PEEK()), REG_BADRPT);
		/* FALLTHROUGH */
	default:
		ordinary(p, c);
		break;
	}

	if (!MORE())
		return;
	c = PEEK();
	/* we call { a repetition if followed by a digit */
	if (!( c == '*' || c == '+' || c == '?' ||
				(c == '{' && MORE2() && ISDIGIT((UCHAR_T)PEEK2())) ))
		return;		/* no repetition, we're done */
	NEXT();

	(void)REQUIRE(!wascaret, REG_BADRPT);
	switch (c) {
	case '*':	/* implemented as +? */
		/* this case does not require the (y|) trick, noKLUDGE */
		INSERT(OPLUS_, pos);
		ASTERN(O_PLUS, pos);
		INSERT(OQUEST_, pos);
		ASTERN(O_QUEST, pos);
		break;
	case '+':
		INSERT(OPLUS_, pos);
		ASTERN(O_PLUS, pos);
		break;
	case '?':
		/* KLUDGE: emit y? as (y|) until subtle bug gets fixed */
		INSERT(OCH_, pos);		/* offset slightly wrong */
		ASTERN(OOR1, pos);		/* this one's right */
		AHEAD(pos);			/* fix the OCH_ */
		EMIT(OOR2, 0);			/* offset very wrong... */
		AHEAD(THERE());			/* ...so fix it */
		ASTERN(O_CH, THERETHERE());
		break;
	case '{':
		count = p_count(p);
		if (EAT(',')) {
			if (ISDIGIT((UCHAR_T)PEEK())) {
				count2 = p_count(p);
				(void)REQUIRE(count <= count2, REG_BADBR);
			} else		/* single number with comma */
				count2 = INFINITY;
		} else		/* just a single number */
			count2 = count;
		repeat(p, pos, count, count2, 0);
		if (!EAT('}')) {	/* error heuristics */
			while (MORE() && PEEK() != '}')
				NEXT();
			(void)REQUIRE(MORE(), REG_EBRACE);
			SETERROR(REG_BADBR);
		}
		break;
	}

	if (!MORE())
		return;
	c = PEEK();
	if (!( c == '*' || c == '+' || c == '?' ||
				(c == '{' && MORE2() && ISDIGIT((UCHAR_T)PEEK2())) ) )
		return;
	SETERROR(REG_BADRPT);
}