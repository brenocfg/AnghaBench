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
typedef  int /*<<< orphan*/  uch ;
struct parse {size_t* pbegin; size_t* pend; TYPE_1__* g; int /*<<< orphan*/ * strip; } ;
typedef  size_t sopno ;
struct TYPE_2__ {size_t nsub; int cflags; int backrefs; int /*<<< orphan*/  neol; int /*<<< orphan*/  iflags; int /*<<< orphan*/  nbol; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHEAD (size_t) ; 
 int /*<<< orphan*/  ASTERN (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  EAT (char) ; 
 int /*<<< orphan*/  EMIT (int /*<<< orphan*/ ,int) ; 
 char GETNEXT () ; 
 void* HERE () ; 
 int INFINITY ; 
 int /*<<< orphan*/  INSERT (int /*<<< orphan*/ ,size_t) ; 
 int MORE () ; 
 scalar_t__ MORE2 () ; 
 int /*<<< orphan*/  MUSTEAT (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEXT () ; 
 size_t NPAREN ; 
 int /*<<< orphan*/  OANY ; 
 int /*<<< orphan*/  OBACK_ ; 
 int /*<<< orphan*/  OBOL ; 
 int /*<<< orphan*/  OCH_ ; 
 int /*<<< orphan*/  OEOL ; 
 int /*<<< orphan*/  OLPAREN ; 
 int /*<<< orphan*/  OOR1 ; 
 int /*<<< orphan*/  OOR2 ; 
 int /*<<< orphan*/  OP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPLUS_ ; 
 int /*<<< orphan*/  OQUEST_ ; 
 int /*<<< orphan*/  ORPAREN ; 
 int /*<<< orphan*/  O_BACK ; 
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
 int /*<<< orphan*/  REG_ESUBREG ; 
 int REG_NEWLINE ; 
 int /*<<< orphan*/  REQUIRE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEE (char) ; 
 int /*<<< orphan*/  SETERROR (int /*<<< orphan*/ ) ; 
 size_t THERE () ; 
 size_t THERETHERE () ; 
 int /*<<< orphan*/  USEBOL ; 
 int /*<<< orphan*/  USEEOL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dupl (struct parse*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ isdigit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nonnewline (struct parse*) ; 
 int /*<<< orphan*/  ordinary (struct parse*,char) ; 
 int /*<<< orphan*/  p_bracket (struct parse*) ; 
 int p_count (struct parse*) ; 
 int /*<<< orphan*/  p_ere (struct parse*,char) ; 
 int /*<<< orphan*/  repeat (struct parse*,size_t,int,int) ; 

__attribute__((used)) static void
p_ere_exp(struct parse *p)
{
	char c;
	sopno pos;
	int count;
	int count2;
	int backrefnum;
	sopno subno;
	int wascaret = 0;

	assert(MORE());		/* caller should have ensured this */
	c = GETNEXT();

	pos = HERE();
	switch (c) {
	case '(':
		REQUIRE(MORE(), REG_EPAREN);
		p->g->nsub++;
		subno = p->g->nsub;
		if (subno < NPAREN)
			p->pbegin[subno] = HERE();
		EMIT(OLPAREN, subno);
		if (!SEE(')'))
			p_ere(p, ')');
		if (subno < NPAREN) {
			p->pend[subno] = HERE();
			assert(p->pend[subno] != 0);
		}
		EMIT(ORPAREN, subno);
		MUSTEAT(')', REG_EPAREN);
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
		REQUIRE(MORE(), REG_EESCAPE);
		c = GETNEXT();
		if (c >= '1' && c <= '9') {
			/* \[0-9] is taken to be a back-reference to a previously specified
			 * matching group. backrefnum will hold the number. The matching
			 * group must exist (i.e. if \4 is found there must have been at
			 * least 4 matching groups specified in the pattern previously).
			 */
			backrefnum = c - '0';
			if (p->pend[backrefnum] == 0) {
				SETERROR(REG_ESUBREG);
				break;
			}

			/* Make sure everything checks out and emit the sequence
			 * that marks a back-reference to the parse structure.
			 */
			assert(backrefnum <= p->g->nsub);
			EMIT(OBACK_, backrefnum);
			assert(p->pbegin[backrefnum] != 0);
			assert(OP(p->strip[p->pbegin[backrefnum]]) != OLPAREN);
			assert(OP(p->strip[p->pend[backrefnum]]) != ORPAREN);
			(void) dupl(p, p->pbegin[backrefnum]+1, p->pend[backrefnum]);
			EMIT(O_BACK, backrefnum);
			p->g->backrefs = 1;
		} else {
			/* Other chars are simply themselves when escaped with a backslash.
			 */
			ordinary(p, c);
		}
		break;
	case '{':		/* okay as ordinary except if digit follows */
		REQUIRE(!MORE() || !isdigit((uch)PEEK()), REG_BADRPT);
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
				(c == '{' && MORE2() && isdigit((uch)PEEK2())) ))
		return;		/* no repetition, we're done */
	NEXT();

	REQUIRE(!wascaret, REG_BADRPT);
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
			if (isdigit((uch)PEEK())) {
				count2 = p_count(p);
				REQUIRE(count <= count2, REG_BADBR);
			} else		/* single number with comma */
				count2 = INFINITY;
		} else		/* just a single number */
			count2 = count;
		repeat(p, pos, count, count2);
		if (!EAT('}')) {	/* error heuristics */
			while (MORE() && PEEK() != '}')
				NEXT();
			REQUIRE(MORE(), REG_EBRACE);
			SETERROR(REG_BADBR);
		}
		break;
	}

	if (!MORE())
		return;
	c = PEEK();
	if (!( c == '*' || c == '+' || c == '?' ||
				(c == '{' && MORE2() && isdigit((uch)PEEK2())) ) )
		return;
	SETERROR(REG_BADRPT);
}