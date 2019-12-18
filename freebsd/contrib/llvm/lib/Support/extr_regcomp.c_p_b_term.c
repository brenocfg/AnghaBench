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
struct parse {int dummy; } ;
typedef  int /*<<< orphan*/  cset ;

/* Variables and functions */
 int /*<<< orphan*/  CHadd (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EAT (char) ; 
 int EATTWO (char,char) ; 
 int MORE () ; 
 int /*<<< orphan*/  MORE2 () ; 
 int /*<<< orphan*/  NEXT () ; 
 int /*<<< orphan*/  NEXT2 () ; 
 int PEEK () ; 
 char PEEK2 () ; 
 int /*<<< orphan*/  REG_EBRACK ; 
 int /*<<< orphan*/  REG_ECOLLATE ; 
 int /*<<< orphan*/  REG_ECTYPE ; 
 int /*<<< orphan*/  REG_ERANGE ; 
 int /*<<< orphan*/  REQUIRE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEE (char) ; 
 int /*<<< orphan*/  SETERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_b_cclass (struct parse*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_b_eclass (struct parse*,int /*<<< orphan*/ *) ; 
 char p_b_symbol (struct parse*) ; 

__attribute__((used)) static void
p_b_term(struct parse *p, cset *cs)
{
	char c;
	char start, finish;
	int i;

	/* classify what we've got */
	switch ((MORE()) ? PEEK() : '\0') {
	case '[':
		c = (MORE2()) ? PEEK2() : '\0';
		break;
	case '-':
		SETERROR(REG_ERANGE);
		return;			/* NOTE RETURN */
		break;
	default:
		c = '\0';
		break;
	}

	switch (c) {
	case ':':		/* character class */
		NEXT2();
		REQUIRE(MORE(), REG_EBRACK);
		c = PEEK();
		REQUIRE(c != '-' && c != ']', REG_ECTYPE);
		p_b_cclass(p, cs);
		REQUIRE(MORE(), REG_EBRACK);
		REQUIRE(EATTWO(':', ']'), REG_ECTYPE);
		break;
	case '=':		/* equivalence class */
		NEXT2();
		REQUIRE(MORE(), REG_EBRACK);
		c = PEEK();
		REQUIRE(c != '-' && c != ']', REG_ECOLLATE);
		p_b_eclass(p, cs);
		REQUIRE(MORE(), REG_EBRACK);
		REQUIRE(EATTWO('=', ']'), REG_ECOLLATE);
		break;
	default:		/* symbol, ordinary character, or range */
/* xxx revision needed for multichar stuff */
		start = p_b_symbol(p);
		if (SEE('-') && MORE2() && PEEK2() != ']') {
			/* range */
			NEXT();
			if (EAT('-'))
				finish = '-';
			else
				finish = p_b_symbol(p);
		} else
			finish = start;
/* xxx what about signed chars here... */
		REQUIRE(start <= finish, REG_ERANGE);
		for (i = start; i <= finish; i++)
			CHadd(cs, i);
		break;
	}
}