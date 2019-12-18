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
struct gdstate {int Year; int Day; int Month; int Hour; int Minutes; TYPE_1__* tokenp; scalar_t__ Seconds; scalar_t__ HaveTime; int /*<<< orphan*/  HaveDay; int /*<<< orphan*/  HaveMonth; int /*<<< orphan*/  HaveYear; int /*<<< orphan*/  HaveRel; int /*<<< orphan*/  RelMonth; int /*<<< orphan*/  RelSeconds; } ;
struct TYPE_2__ {scalar_t__ token; int value; } ;

/* Variables and functions */
 scalar_t__ datephrase (struct gdstate*) ; 
 scalar_t__ dayphrase (struct gdstate*) ; 
 scalar_t__ relunitphrase (struct gdstate*) ; 
 scalar_t__ tAGO ; 
 scalar_t__ tUNUMBER ; 
 scalar_t__ timephrase (struct gdstate*) ; 
 scalar_t__ zonephrase (struct gdstate*) ; 

__attribute__((used)) static int
phrase(struct gdstate *gds)
{
	if (timephrase(gds))
		return 1;
	if (zonephrase(gds))
		return 1;
	if (datephrase(gds))
		return 1;
	if (dayphrase(gds))
		return 1;
	if (relunitphrase(gds)) {
		if (gds->tokenp[0].token == tAGO) {
			gds->RelSeconds = -gds->RelSeconds;
			gds->RelMonth = -gds->RelMonth;
			gds->tokenp += 1;
		}
		return 1;
	}

	/* Bare numbers sometimes have meaning. */
	if (gds->tokenp[0].token == tUNUMBER) {
		if (gds->HaveTime && !gds->HaveYear && !gds->HaveRel) {
			gds->HaveYear++;
			gds->Year = gds->tokenp[0].value;
			gds->tokenp += 1;
			return 1;
		}

		if(gds->tokenp[0].value > 10000) {
			/* "20040301" */
			gds->HaveYear++;
			gds->HaveMonth++;
			gds->HaveDay++;
			gds->Day= (gds->tokenp[0].value)%100;
			gds->Month= (gds->tokenp[0].value/100)%100;
			gds->Year = gds->tokenp[0].value/10000;
			gds->tokenp += 1;
			return 1;
		}

		if (gds->tokenp[0].value < 24) {
			gds->HaveTime++;
			gds->Hour = gds->tokenp[0].value;
			gds->Minutes = 0;
			gds->Seconds = 0;
			gds->tokenp += 1;
			return 1;
		}

		if ((gds->tokenp[0].value / 100 < 24)
		    && (gds->tokenp[0].value % 100 < 60)) {
			/* "513" is same as "5:13" */
			gds->Hour = gds->tokenp[0].value / 100;
			gds->Minutes = gds->tokenp[0].value % 100;
			gds->Seconds = 0;
			gds->tokenp += 1;
			return 1;
		}
	}

	return 0;
}