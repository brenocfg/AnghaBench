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
struct parse {size_t* pbegin; size_t* pend; TYPE_1__* g; int /*<<< orphan*/ * strip; } ;
typedef  size_t sopno ;
typedef  int /*<<< orphan*/  UCHAR_T ;
struct TYPE_2__ {size_t nsub; int backrefs; int cflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASTERN (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ EAT (char) ; 
 int EATTWO (char,char) ; 
 int /*<<< orphan*/  EMIT (int /*<<< orphan*/ ,int) ; 
 int GETNEXT () ; 
 void* HERE () ; 
 int INFINITY ; 
 int /*<<< orphan*/  INSERT (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ ISDIGIT (int /*<<< orphan*/ ) ; 
 int MORE () ; 
 int /*<<< orphan*/  NEXT () ; 
 size_t NPAREN ; 
 int /*<<< orphan*/  OANY ; 
 int /*<<< orphan*/  OBACK_ ; 
 int /*<<< orphan*/  OLPAREN ; 
 int /*<<< orphan*/  OPLUS_ ; 
 int /*<<< orphan*/  OQUEST_ ; 
 int /*<<< orphan*/  ORPAREN ; 
 int /*<<< orphan*/  O_BACK ; 
 int /*<<< orphan*/  O_PLUS ; 
 int /*<<< orphan*/  O_QUEST ; 
 scalar_t__ PEEK () ; 
 int /*<<< orphan*/  REG_BADBR ; 
 int /*<<< orphan*/  REG_BADRPT ; 
 int /*<<< orphan*/  REG_EBRACE ; 
 int /*<<< orphan*/  REG_EESCAPE ; 
 int /*<<< orphan*/  REG_EPAREN ; 
 int /*<<< orphan*/  REG_ESUBREG ; 
 int REG_NEWLINE ; 
 int /*<<< orphan*/  REQUIRE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEETWO (char,char) ; 
 int /*<<< orphan*/  SETERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dupl (struct parse*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  nonnewline (struct parse*) ; 
 int /*<<< orphan*/  ordinary (struct parse*,int) ; 
 int /*<<< orphan*/  p_bracket (struct parse*) ; 
 int /*<<< orphan*/  p_bre (struct parse*,char,char,size_t) ; 
 int p_count (struct parse*) ; 
 int /*<<< orphan*/  repeat (struct parse*,size_t,int,int,size_t) ; 

__attribute__((used)) static int			/* was the simple RE an unbackslashed $? */
p_simp_re(struct parse *p,
    int starordinary,		/* is a leading * an ordinary character? */
    size_t reclimit)
{
	int c;
	int count;
	int count2;
	sopno pos;
	int i;
	sopno subno;
	int backsl;

	pos = HERE();		/* repetion op, if any, covers from here */

	assert(MORE());		/* caller should have ensured this */
	c = GETNEXT();
	backsl = c == '\\';
	if (backsl) {
		(void)REQUIRE(MORE(), REG_EESCAPE);
		c = (unsigned char)GETNEXT();
		switch (c) {
		case '{':
			SETERROR(REG_BADRPT);
			break;
		case '(':
			p->g->nsub++;
			subno = p->g->nsub;
			if (subno < NPAREN)
				p->pbegin[subno] = HERE();
			EMIT(OLPAREN, subno);
			/* the MORE here is an error heuristic */
			if (MORE() && !SEETWO('\\', ')'))
				p_bre(p, '\\', ')', reclimit);
			if (subno < NPAREN) {
				p->pend[subno] = HERE();
				assert(p->pend[subno] != 0);
			}
			EMIT(ORPAREN, subno);
			(void)REQUIRE(EATTWO('\\', ')'), REG_EPAREN);
			break;
		case ')':	/* should not get here -- must be user */
		case '}':
			SETERROR(REG_EPAREN);
			break;
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			i = c - '0';
			assert(i < NPAREN);
			if (p->pend[i] != 0) {
				assert(i <= p->g->nsub);
				EMIT(OBACK_, i);
				assert(p->pbegin[i] != 0);
				assert(p->strip[p->pbegin[i]] == OLPAREN);
				assert(p->strip[p->pend[i]] == ORPAREN);
				(void) dupl(p, p->pbegin[i]+1, p->pend[i]);
				EMIT(O_BACK, i);
			} else
				SETERROR(REG_ESUBREG);
			p->g->backrefs = 1;
			break;
		default:
			ordinary(p, c);
			break;
		}
	} else {
		switch (c) {
		case '.':
			if (p->g->cflags&REG_NEWLINE)
				nonnewline(p);
			else
				EMIT(OANY, 0);
			break;
		case '[':
			p_bracket(p);
			break;
		case '*':
			(void)REQUIRE(starordinary, REG_BADRPT);
			/* FALLTHROUGH */
		default:
			ordinary(p, c);
			break;
		}
	}

	if (EAT('*')) {		/* implemented as +? */
		/* this case does not require the (y|) trick, noKLUDGE */
		INSERT(OPLUS_, pos);
		ASTERN(O_PLUS, pos);
		INSERT(OQUEST_, pos);
		ASTERN(O_QUEST, pos);
	} else if (EATTWO('\\', '{')) {
		count = p_count(p);
		if (EAT(',')) {
			if (MORE() && ISDIGIT((UCHAR_T)PEEK())) {
				count2 = p_count(p);
				(void)REQUIRE(count <= count2, REG_BADBR);
			} else		/* single number with comma */
				count2 = INFINITY;
		} else		/* just a single number */
			count2 = count;
		repeat(p, pos, count, count2, reclimit);
		if (!EATTWO('\\', '}')) {	/* error heuristics */
			while (MORE() && !SEETWO('\\', '}'))
				NEXT();
			(void)REQUIRE(MORE(), REG_EBRACE);
			SETERROR(REG_BADBR);
		}
	} else if (!backsl && c == (unsigned char)'$')	/* $ (but not \$) ends it */
		return(1);

	return(0);
}