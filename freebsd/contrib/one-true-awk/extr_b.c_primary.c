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
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
#define  ALL 133 
#define  CCL 132 
#define  CHAR 131 
#define  DOT 130 
#define  EMPTYRE 129 
 int /*<<< orphan*/  FATAL (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HAT ; 
#define  NCCL 128 
 int /*<<< orphan*/ * NIL ; 
 void* basestr ; 
 scalar_t__ cclenter (char*) ; 
 int /*<<< orphan*/ * itonp (int /*<<< orphan*/ ) ; 
 void* lastatom ; 
 int /*<<< orphan*/  lastre ; 
 int /*<<< orphan*/ * op2 (int const,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prestr ; 
 int /*<<< orphan*/ * regexp () ; 
 int relex () ; 
 scalar_t__ rlxstr ; 
 int /*<<< orphan*/  rlxval ; 
 int rtok ; 
 void* starttok ; 
 scalar_t__ tostring (char*) ; 
 int /*<<< orphan*/ * unary (int /*<<< orphan*/ *) ; 

Node *primary(void)
{
	Node *np;
	int savelastatom;

	switch (rtok) {
	case CHAR:
		lastatom = starttok;
		np = op2(CHAR, NIL, itonp(rlxval));
		rtok = relex();
		return (unary(np));
	case ALL:
		rtok = relex();
		return (unary(op2(ALL, NIL, NIL)));
	case EMPTYRE:
		rtok = relex();
		return (unary(op2(EMPTYRE, NIL, NIL)));
	case DOT:
		lastatom = starttok;
		rtok = relex();
		return (unary(op2(DOT, NIL, NIL)));
	case CCL:
		np = op2(CCL, NIL, (Node*) cclenter((char *) rlxstr));
		lastatom = starttok;
		rtok = relex();
		return (unary(np));
	case NCCL:
		np = op2(NCCL, NIL, (Node *) cclenter((char *) rlxstr));
		lastatom = starttok;
		rtok = relex();
		return (unary(np));
	case '^':
		rtok = relex();
		return (unary(op2(CHAR, NIL, itonp(HAT))));
	case '$':
		rtok = relex();
		return (unary(op2(CHAR, NIL, NIL)));
	case '(':
		lastatom = starttok;
		savelastatom = starttok - basestr; /* Retain over recursion */
		rtok = relex();
		if (rtok == ')') {	/* special pleading for () */
			rtok = relex();
			return unary(op2(CCL, NIL, (Node *) tostring("")));
		}
		np = regexp();
		if (rtok == ')') {
			lastatom = basestr + savelastatom; /* Restore */
			rtok = relex();
			return (unary(np));
		}
		else
			FATAL("syntax error in regular expression %s at %s", lastre, prestr);
	default:
		FATAL("illegal primary in regular expression %s at %s", lastre, prestr);
	}
	return 0;	/*NOTREACHED*/
}