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
struct re_guts {int /*<<< orphan*/ * strip; int /*<<< orphan*/ * sets; } ;
typedef  int /*<<< orphan*/  states ;
typedef  size_t sopno ;
typedef  int /*<<< orphan*/  sop ;
typedef  int /*<<< orphan*/  onestate ;
typedef  int /*<<< orphan*/  cset ;

/* Variables and functions */
 int /*<<< orphan*/  BACK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int BOL ; 
 int BOLEOL ; 
 int BOW ; 
 int /*<<< orphan*/  CHIN (int /*<<< orphan*/ *,int) ; 
 int EOL ; 
 int EOW ; 
 int /*<<< orphan*/  FWD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT (int /*<<< orphan*/ ,size_t) ; 
 int ISSETBACK (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ISSTATEIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NONCHAR (int) ; 
#define  OANY 147 
#define  OANYOF 146 
#define  OBACK_ 145 
#define  OBOL 144 
#define  OBOW 143 
#define  OCHAR 142 
#define  OCH_ 141 
#define  OEND 140 
#define  OEOL 139 
#define  OEOW 138 
#define  OLPAREN 137 
#define  OOR1 136 
#define  OOR2 135 
 int const OP (int /*<<< orphan*/ ) ; 
#define  OPLUS_ 134 
 int OPND (int /*<<< orphan*/ ) ; 
#define  OQUEST_ 133 
#define  ORPAREN 132 
#define  O_BACK 131 
#define  O_CH 130 
#define  O_PLUS 129 
#define  O_QUEST 128 
 int /*<<< orphan*/  assert (int) ; 
 int nope ; 

__attribute__((used)) static states
step(struct re_guts *g,
    sopno start,		/* start state within strip */
    sopno stop,			/* state after stop state within strip */
    states bef,			/* states reachable before */
    int ch,			/* character or NONCHAR code */
    states aft)			/* states already known reachable after */
{
	cset *cs;
	sop s;
	sopno pc;
	onestate here;		/* note, macros know this name */
	sopno look;
	int i;

	for (pc = start, INIT(here, pc); pc != stop; pc++, INC(here)) {
		s = g->strip[pc];
		switch (OP(s)) {
		case OEND:
			assert(pc == stop-1);
			break;
		case OCHAR:
			/* only characters can match */
			assert(!NONCHAR(ch) || ch != (char)OPND(s));
			if (ch == (char)OPND(s))
				FWD(aft, bef, 1);
			break;
		case OBOL:
			if (ch == BOL || ch == BOLEOL)
				FWD(aft, bef, 1);
			break;
		case OEOL:
			if (ch == EOL || ch == BOLEOL)
				FWD(aft, bef, 1);
			break;
		case OBOW:
			if (ch == BOW)
				FWD(aft, bef, 1);
			break;
		case OEOW:
			if (ch == EOW)
				FWD(aft, bef, 1);
			break;
		case OANY:
			if (!NONCHAR(ch))
				FWD(aft, bef, 1);
			break;
		case OANYOF:
			cs = &g->sets[OPND(s)];
			if (!NONCHAR(ch) && CHIN(cs, ch))
				FWD(aft, bef, 1);
			break;
		case OBACK_:		/* ignored here */
		case O_BACK:
			FWD(aft, aft, 1);
			break;
		case OPLUS_:		/* forward, this is just an empty */
			FWD(aft, aft, 1);
			break;
		case O_PLUS:		/* both forward and back */
			FWD(aft, aft, 1);
			i = ISSETBACK(aft, OPND(s));
			BACK(aft, aft, OPND(s));
			if (!i && ISSETBACK(aft, OPND(s))) {
				/* oho, must reconsider loop body */
				pc -= OPND(s) + 1;
				INIT(here, pc);
			}
			break;
		case OQUEST_:		/* two branches, both forward */
			FWD(aft, aft, 1);
			FWD(aft, aft, OPND(s));
			break;
		case O_QUEST:		/* just an empty */
			FWD(aft, aft, 1);
			break;
		case OLPAREN:		/* not significant here */
		case ORPAREN:
			FWD(aft, aft, 1);
			break;
		case OCH_:		/* mark the first two branches */
			FWD(aft, aft, 1);
			assert(OP(g->strip[pc+OPND(s)]) == OOR2);
			FWD(aft, aft, OPND(s));
			break;
		case OOR1:		/* done a branch, find the O_CH */
			if (ISSTATEIN(aft, here)) {
				for (look = 1;
						OP(s = g->strip[pc+look]) != O_CH;
						look += OPND(s))
					assert(OP(s) == OOR2);
				FWD(aft, aft, look);
			}
			break;
		case OOR2:		/* propagate OCH_'s marking */
			FWD(aft, aft, 1);
			if (OP(g->strip[pc+OPND(s)]) != O_CH) {
				assert(OP(g->strip[pc+OPND(s)]) == OOR2);
				FWD(aft, aft, OPND(s));
			}
			break;
		case O_CH:		/* just empty */
			FWD(aft, aft, 1);
			break;
		default:		/* ooooops... */
			assert(nope);
			break;
		}
	}

	return(aft);
}