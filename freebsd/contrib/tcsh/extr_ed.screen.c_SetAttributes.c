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
typedef  int Char ;

/* Variables and functions */
 int ATTRIBUTES ; 
 int BOLD ; 
 scalar_t__ GoodStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUTPURE ; 
 int STANDOUT ; 
 int /*<<< orphan*/  Str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_md ; 
 int /*<<< orphan*/  T_me ; 
 int /*<<< orphan*/  T_se ; 
 int /*<<< orphan*/  T_so ; 
 int /*<<< orphan*/  T_ue ; 
 int /*<<< orphan*/  T_us ; 
 int UNDER ; 
 int cur_atr ; 
 scalar_t__ me_all ; 
 int /*<<< orphan*/  tputs (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
SetAttributes(Char atr)
{
    atr &= ATTRIBUTES;
    if (atr != cur_atr) {
	if (me_all && GoodStr(T_me)) {
	    if (((cur_atr & BOLD) && !(atr & BOLD)) ||
		((cur_atr & UNDER) && !(atr & UNDER)) ||
		((cur_atr & STANDOUT) && !(atr & STANDOUT))) {
		(void) tputs(Str(T_me), 1, PUTPURE);
		cur_atr = 0;
	    }
	}
	if ((atr & BOLD) != (cur_atr & BOLD)) {
	    if (atr & BOLD) {
		if (GoodStr(T_md) && GoodStr(T_me)) {
		    (void) tputs(Str(T_md), 1, PUTPURE);
		    cur_atr |= BOLD;
		}
	    }
	    else {
		if (GoodStr(T_md) && GoodStr(T_me)) {
		    (void) tputs(Str(T_me), 1, PUTPURE);
		    if ((cur_atr & STANDOUT) && GoodStr(T_se)) {
			(void) tputs(Str(T_se), 1, PUTPURE);
			cur_atr &= ~STANDOUT;
		    }
		    if ((cur_atr & UNDER) && GoodStr(T_ue)) {
			(void) tputs(Str(T_ue), 1, PUTPURE);
			cur_atr &= ~UNDER;
		    }
		    cur_atr &= ~BOLD;
		}
	    }
	}
	if ((atr & STANDOUT) != (cur_atr & STANDOUT)) {
	    if (atr & STANDOUT) {
		if (GoodStr(T_so) && GoodStr(T_se)) {
		    (void) tputs(Str(T_so), 1, PUTPURE);
		    cur_atr |= STANDOUT;
		}
	    }
	    else {
		if (GoodStr(T_se)) {
		    (void) tputs(Str(T_se), 1, PUTPURE);
		    cur_atr &= ~STANDOUT;
		}
	    }
	}
	if ((atr & UNDER) != (cur_atr & UNDER)) {
	    if (atr & UNDER) {
		if (GoodStr(T_us) && GoodStr(T_ue)) {
		    (void) tputs(Str(T_us), 1, PUTPURE);
		    cur_atr |= UNDER;
		}
	    }
	    else {
		if (GoodStr(T_ue)) {
		    (void) tputs(Str(T_ue), 1, PUTPURE);
		    cur_atr &= ~UNDER;
		}
	    }
	}
    }
}