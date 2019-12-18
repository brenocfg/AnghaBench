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
struct re_guts {int* strip; size_t* stripdata; int /*<<< orphan*/ * sets; } ;
typedef  int /*<<< orphan*/  states ;
typedef  size_t sopno ;
typedef  int sop ;
typedef  int /*<<< orphan*/  onestate ;
typedef  int /*<<< orphan*/  cset ;
typedef  size_t RCHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  BACK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int BOL ; 
 int BOLEOL ; 
 int BOW ; 
 int /*<<< orphan*/  CHIN (int /*<<< orphan*/ *,size_t) ; 
 int EOL ; 
 int EOW ; 
 int /*<<< orphan*/  FWD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT (int /*<<< orphan*/ ,size_t) ; 
 int ISSETBACK (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ISSTATEIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
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
 int OP (int) ; 
#define  OPLUS_ 134 
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
    sopno start,			/* start state within strip */
    sopno stop,			/* state after stop state within strip */
    states bef,		/* states reachable before */
    int flag,			/* NONCHAR flag */
    RCHAR_T ch,			/* character code */
    states aft)		/* states already known reachable after */
{
	cset *cs;
	sop s;
	RCHAR_T d;
	sopno pc;
	onestate here;		/* note, macros know this name */
	sopno look;
	int i;

	for (pc = start, INIT(here, pc); pc != stop; pc++, INC(here)) {
		s = g->strip[pc];
		d = g->stripdata[pc];
		switch (s) {
		case OEND:
			assert(pc == stop-1);
			break;
		case OCHAR:
			/* only characters can match */
			assert(!flag || ch != d);
			if (ch == d)
				FWD(aft, bef, 1);
			break;
		case OBOL:
			if (flag == BOL || flag == BOLEOL)
				FWD(aft, bef, 1);
			break;
		case OEOL:
			if (flag == EOL || flag == BOLEOL)
				FWD(aft, bef, 1);
			break;
		case OBOW:
			if (flag == BOW)
				FWD(aft, bef, 1);
			break;
		case OEOW:
			if (flag == EOW)
				FWD(aft, bef, 1);
			break;
		case OANY:
			if (!flag)
				FWD(aft, bef, 1);
			break;
		case OANYOF:
			cs = &g->sets[d];
			if (!flag && CHIN(cs, ch))
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
			i = ISSETBACK(aft, d);
			BACK(aft, aft, d);
			if (!i && ISSETBACK(aft, d)) {
				/* oho, must reconsider loop body */
				pc -= d + 1;
				INIT(here, pc);
			}
			break;
		case OQUEST_:		/* two branches, both forward */
			FWD(aft, aft, 1);
			FWD(aft, aft, d);
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
			assert(OP(g->strip[pc+d]) == OOR2);
			FWD(aft, aft, d);
			break;
		case OOR1:		/* done a branch, find the O_CH */
			if (ISSTATEIN(aft, here)) {
				for (look = 1; /**/; look += d) {
					s = g->strip[pc+look];
					d = g->stripdata[pc+look];
					if (s == O_CH)
						break;
					assert(s == OOR2);
				}
				FWD(aft, aft, look);
			}
			break;
		case OOR2:		/* propagate OCH_'s marking */
			FWD(aft, aft, 1);
			if (g->strip[pc+d] != O_CH) {
				assert(g->strip[pc+d] == OOR2);
				FWD(aft, aft, d);
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