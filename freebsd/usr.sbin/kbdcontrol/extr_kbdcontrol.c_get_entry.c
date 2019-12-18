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

/* Variables and functions */
 int ACC (int) ; 
 int ALK ; 
 int ASH ; 
 int BTAB ; 
 int CLK ; 
 int DBG ; 
 int F (int) ; 
 int HALT ; 
 int LALT ; 
 int LALTA ; 
 int LCTR ; 
 int LCTRA ; 
 int LSH ; 
 int LSHA ; 
 int L_ACC ; 
 int L_FN ; 
 int L_SCR ; 
 int META ; 
 int NEXT ; 
 int NLK ; 
 int NOP ; 
 int PASTE ; 
 int PDWN ; 
 int PNC ; 
 int PREV ; 
 int RALT ; 
 int RALTA ; 
 int RBT ; 
 int RCTR ; 
 int RCTRA ; 
 int RSH ; 
 int RSHA ; 
 int S (int) ; 
 int SLK ; 
 int SPECIAL ; 
 int SPSC ; 
 int SUSP ; 
#define  TACC 162 
#define  TALK 161 
#define  TASH 160 
#define  TBTAB 159 
#define  TCLK 158 
#define  TDBG 157 
#define  TFUNC 156 
#define  THALT 155 
#define  TLALT 154 
#define  TLALTA 153 
#define  TLCTR 152 
#define  TLCTRA 151 
#define  TLET 150 
#define  TLSH 149 
#define  TLSHA 148 
#define  TMETA 147 
#define  TNEXT 146 
#define  TNLK 145 
#define  TNOP 144 
#define  TNUM 143 
#define  TPANIC 142 
#define  TPASTE 141 
#define  TPDWN 140 
#define  TPREV 139 
#define  TRALT 138 
#define  TRALTA 137 
#define  TRBT 136 
#define  TRCTR 135 
#define  TRCTRA 134 
#define  TRSH 133 
#define  TRSHA 132 
#define  TSCRN 131 
#define  TSLK 130 
#define  TSPSC 129 
#define  TSUSP 128 
 scalar_t__ letter ; 
 int number ; 
 int /*<<< orphan*/  token ; 
 int /*<<< orphan*/  yylex () ; 

__attribute__((used)) static int
get_entry(void)
{
	switch ((token = yylex())) {
	case TNOP:
		return NOP | SPECIAL;
	case TLSH:
		return LSH | SPECIAL;
	case TRSH:
		return RSH | SPECIAL;
	case TCLK:
		return CLK | SPECIAL;
	case TNLK:
		return NLK | SPECIAL;
	case TSLK:
		return SLK | SPECIAL;
	case TBTAB:
		return BTAB | SPECIAL;
	case TLALT:
		return LALT | SPECIAL;
	case TLCTR:
		return LCTR | SPECIAL;
	case TNEXT:
		return NEXT | SPECIAL;
	case TPREV:
		return PREV | SPECIAL;
	case TRCTR:
		return RCTR | SPECIAL;
	case TRALT:
		return RALT | SPECIAL;
	case TALK:
		return ALK | SPECIAL;
	case TASH:
		return ASH | SPECIAL;
	case TMETA:
		return META | SPECIAL;
	case TRBT:
		return RBT | SPECIAL;
	case TDBG:
		return DBG | SPECIAL;
	case TSUSP:
		return SUSP | SPECIAL;
	case TSPSC:
		return SPSC | SPECIAL;
	case TPANIC:
		return PNC | SPECIAL;
	case TLSHA:
		return LSHA | SPECIAL;
	case TRSHA:
		return RSHA | SPECIAL;
	case TLCTRA:
		return LCTRA | SPECIAL;
	case TRCTRA:
		return RCTRA | SPECIAL;
	case TLALTA:
		return LALTA | SPECIAL;
	case TRALTA:
		return RALTA | SPECIAL;
	case THALT:
		return HALT | SPECIAL;
	case TPDWN:
		return PDWN | SPECIAL;
	case TPASTE:
		return PASTE | SPECIAL;
	case TACC:
		if (ACC(number) > L_ACC)
			return -1;
		return ACC(number) | SPECIAL;
	case TFUNC:
		if (F(number) > L_FN)
			return -1;
		return F(number) | SPECIAL;
	case TSCRN:
		if (S(number) > L_SCR)
			return -1;
		return S(number) | SPECIAL;
	case TLET:
		return (unsigned char)letter;
	case TNUM:
		if (number < 0x000000 || number > 0x10FFFF)
			return -1;
		return number;
	default:
		return -1;
	}
}