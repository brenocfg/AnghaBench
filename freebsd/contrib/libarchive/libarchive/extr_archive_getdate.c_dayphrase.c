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
struct gdstate {int DayOrdinal; int DayNumber; TYPE_1__* tokenp; int /*<<< orphan*/  HaveWeekDay; } ;
struct TYPE_2__ {char token; int value; } ;

/* Variables and functions */
 char tDAY ; 
 char tUNUMBER ; 

__attribute__((used)) static int
dayphrase(struct gdstate *gds)
{
	if (gds->tokenp[0].token == tDAY) {
		/* "tues", "wednesday," */
		gds->HaveWeekDay++;
		gds->DayOrdinal = 1;
		gds->DayNumber = gds->tokenp[0].value;
		gds->tokenp += 1;
		if (gds->tokenp[0].token == ',')
			gds->tokenp += 1;
		return 1;
	}
	if (gds->tokenp[0].token == tUNUMBER
		&& gds->tokenp[1].token == tDAY) {
		/* "second tues" "3 wed" */
		gds->HaveWeekDay++;
		gds->DayOrdinal = gds->tokenp[0].value;
		gds->DayNumber = gds->tokenp[1].value;
		gds->tokenp += 2;
		return 1;
	}
	return 0;
}