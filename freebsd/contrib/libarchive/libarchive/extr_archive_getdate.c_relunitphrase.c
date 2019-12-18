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
struct gdstate {int RelSeconds; int RelMonth; TYPE_1__* tokenp; int /*<<< orphan*/  HaveRel; } ;
struct TYPE_2__ {char token; int value; } ;

/* Variables and functions */
 char tMONTH_UNIT ; 
 char tSEC_UNIT ; 
 char tUNUMBER ; 

__attribute__((used)) static int
relunitphrase(struct gdstate *gds)
{
	if (gds->tokenp[0].token == '-'
	    && gds->tokenp[1].token == tUNUMBER
	    && gds->tokenp[2].token == tSEC_UNIT) {
		/* "-3 hours" */
		gds->HaveRel++;
		gds->RelSeconds -= gds->tokenp[1].value * gds->tokenp[2].value;
		gds->tokenp += 3;
		return 1;
	}
	if (gds->tokenp[0].token == '+'
	    && gds->tokenp[1].token == tUNUMBER
	    && gds->tokenp[2].token == tSEC_UNIT) {
		/* "+1 minute" */
		gds->HaveRel++;
		gds->RelSeconds += gds->tokenp[1].value * gds->tokenp[2].value;
		gds->tokenp += 3;
		return 1;
	}
	if (gds->tokenp[0].token == tUNUMBER
	    && gds->tokenp[1].token == tSEC_UNIT) {
		/* "1 day" */
		gds->HaveRel++;
		gds->RelSeconds += gds->tokenp[0].value * gds->tokenp[1].value;
		gds->tokenp += 2;
		return 1;
	}
	if (gds->tokenp[0].token == '-'
	    && gds->tokenp[1].token == tUNUMBER
	    && gds->tokenp[2].token == tMONTH_UNIT) {
		/* "-3 months" */
		gds->HaveRel++;
		gds->RelMonth -= gds->tokenp[1].value * gds->tokenp[2].value;
		gds->tokenp += 3;
		return 1;
	}
	if (gds->tokenp[0].token == '+'
	    && gds->tokenp[1].token == tUNUMBER
	    && gds->tokenp[2].token == tMONTH_UNIT) {
		/* "+5 years" */
		gds->HaveRel++;
		gds->RelMonth += gds->tokenp[1].value * gds->tokenp[2].value;
		gds->tokenp += 3;
		return 1;
	}
	if (gds->tokenp[0].token == tUNUMBER
	    && gds->tokenp[1].token == tMONTH_UNIT) {
		/* "2 years" */
		gds->HaveRel++;
		gds->RelMonth += gds->tokenp[0].value * gds->tokenp[1].value;
		gds->tokenp += 2;
		return 1;
	}
	if (gds->tokenp[0].token == tSEC_UNIT) {
		/* "now", "tomorrow" */
		gds->HaveRel++;
		gds->RelSeconds += gds->tokenp[0].value;
		gds->tokenp += 1;
		return 1;
	}
	if (gds->tokenp[0].token == tMONTH_UNIT) {
		/* "month" */
		gds->HaveRel++;
		gds->RelMonth += gds->tokenp[0].value;
		gds->tokenp += 1;
		return 1;
	}
	return 0;
}