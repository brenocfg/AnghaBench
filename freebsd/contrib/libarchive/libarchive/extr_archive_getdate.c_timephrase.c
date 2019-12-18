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
struct gdstate {int Hour; int Minutes; int Seconds; int Timezone; TYPE_1__* tokenp; void* DSTmode; int /*<<< orphan*/  HaveZone; int /*<<< orphan*/  HaveTime; } ;
struct TYPE_2__ {char token; int value; } ;

/* Variables and functions */
 void* DSToff ; 
 int HOUR ; 
 int MINUTE ; 
 char tAMPM ; 
 int tPM ; 
 char tUNUMBER ; 

__attribute__((used)) static int
timephrase(struct gdstate *gds)
{
	if (gds->tokenp[0].token == tUNUMBER
	    && gds->tokenp[1].token == ':'
	    && gds->tokenp[2].token == tUNUMBER
	    && gds->tokenp[3].token == ':'
	    && gds->tokenp[4].token == tUNUMBER) {
		/* "12:14:18" or "22:08:07" */
		++gds->HaveTime;
		gds->Hour = gds->tokenp[0].value;
		gds->Minutes = gds->tokenp[2].value;
		gds->Seconds = gds->tokenp[4].value;
		gds->tokenp += 5;
	}
	else if (gds->tokenp[0].token == tUNUMBER
	    && gds->tokenp[1].token == ':'
	    && gds->tokenp[2].token == tUNUMBER) {
		/* "12:14" or "22:08" */
		++gds->HaveTime;
		gds->Hour = gds->tokenp[0].value;
		gds->Minutes = gds->tokenp[2].value;
		gds->Seconds = 0;
		gds->tokenp += 3;
	}
	else if (gds->tokenp[0].token == tUNUMBER
	    && gds->tokenp[1].token == tAMPM) {
		/* "7" is a time if it's followed by "am" or "pm" */
		++gds->HaveTime;
		gds->Hour = gds->tokenp[0].value;
		gds->Minutes = gds->Seconds = 0;
		/* We'll handle the AM/PM below. */
		gds->tokenp += 1;
	} else {
		/* We can't handle this. */
		return 0;
	}

	if (gds->tokenp[0].token == tAMPM) {
		/* "7:12pm", "12:20:13am" */
		if (gds->Hour == 12)
			gds->Hour = 0;
		if (gds->tokenp[0].value == tPM)
			gds->Hour += 12;
		gds->tokenp += 1;
	}
	if (gds->tokenp[0].token == '+'
	    && gds->tokenp[1].token == tUNUMBER) {
		/* "7:14+0700" */
		gds->HaveZone++;
		gds->DSTmode = DSToff;
		gds->Timezone = - ((gds->tokenp[1].value / 100) * HOUR
		    + (gds->tokenp[1].value % 100) * MINUTE);
		gds->tokenp += 2;
	}
	if (gds->tokenp[0].token == '-'
	    && gds->tokenp[1].token == tUNUMBER) {
		/* "19:14:12-0530" */
		gds->HaveZone++;
		gds->DSTmode = DSToff;
		gds->Timezone = + ((gds->tokenp[1].value / 100) * HOUR
		    + (gds->tokenp[1].value % 100) * MINUTE);
		gds->tokenp += 2;
	}
	return 1;
}