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
struct gdstate {int Year; int Month; int Day; TYPE_1__* tokenp; int /*<<< orphan*/  HaveDay; int /*<<< orphan*/  HaveMonth; int /*<<< orphan*/  HaveYear; } ;
struct TYPE_2__ {char token; int value; } ;

/* Variables and functions */
 char tMONTH ; 
 char tUNUMBER ; 

__attribute__((used)) static int
datephrase(struct gdstate *gds)
{
	if (gds->tokenp[0].token == tUNUMBER
	    && gds->tokenp[1].token == '/'
	    && gds->tokenp[2].token == tUNUMBER
	    && gds->tokenp[3].token == '/'
	    && gds->tokenp[4].token == tUNUMBER) {
		gds->HaveYear++;
		gds->HaveMonth++;
		gds->HaveDay++;
		if (gds->tokenp[0].value >= 13) {
			/* First number is big:  2004/01/29, 99/02/17 */
			gds->Year = gds->tokenp[0].value;
			gds->Month = gds->tokenp[2].value;
			gds->Day = gds->tokenp[4].value;
		} else if ((gds->tokenp[4].value >= 13)
		    || (gds->tokenp[2].value >= 13)) {
			/* Last number is big:  01/07/98 */
			/* Middle number is big:  01/29/04 */
			gds->Month = gds->tokenp[0].value;
			gds->Day = gds->tokenp[2].value;
			gds->Year = gds->tokenp[4].value;
		} else {
			/* No significant clues: 02/03/04 */
			gds->Month = gds->tokenp[0].value;
			gds->Day = gds->tokenp[2].value;
			gds->Year = gds->tokenp[4].value;
		}
		gds->tokenp += 5;
		return 1;
	}

	if (gds->tokenp[0].token == tUNUMBER
	    && gds->tokenp[1].token == '/'
	    && gds->tokenp[2].token == tUNUMBER) {
		/* "1/15" */
		gds->HaveMonth++;
		gds->HaveDay++;
		gds->Month = gds->tokenp[0].value;
		gds->Day = gds->tokenp[2].value;
		gds->tokenp += 3;
		return 1;
	}

	if (gds->tokenp[0].token == tUNUMBER
	    && gds->tokenp[1].token == '-'
	    && gds->tokenp[2].token == tUNUMBER
	    && gds->tokenp[3].token == '-'
	    && gds->tokenp[4].token == tUNUMBER) {
		/* ISO 8601 format.  yyyy-mm-dd.  */
		gds->HaveYear++;
		gds->HaveMonth++;
		gds->HaveDay++;
		gds->Year = gds->tokenp[0].value;
		gds->Month = gds->tokenp[2].value;
		gds->Day = gds->tokenp[4].value;
		gds->tokenp += 5;
		return 1;
	}

	if (gds->tokenp[0].token == tUNUMBER
	    && gds->tokenp[1].token == '-'
	    && gds->tokenp[2].token == tMONTH
	    && gds->tokenp[3].token == '-'
	    && gds->tokenp[4].token == tUNUMBER) {
		gds->HaveYear++;
		gds->HaveMonth++;
		gds->HaveDay++;
		if (gds->tokenp[0].value > 31) {
			/* e.g. 1992-Jun-17 */
			gds->Year = gds->tokenp[0].value;
			gds->Month = gds->tokenp[2].value;
			gds->Day = gds->tokenp[4].value;
		} else {
			/* e.g. 17-JUN-1992.  */
			gds->Day = gds->tokenp[0].value;
			gds->Month = gds->tokenp[2].value;
			gds->Year = gds->tokenp[4].value;
		}
		gds->tokenp += 5;
		return 1;
	}

	if (gds->tokenp[0].token == tMONTH
	    && gds->tokenp[1].token == tUNUMBER
	    && gds->tokenp[2].token == ','
	    && gds->tokenp[3].token == tUNUMBER) {
		/* "June 17, 2001" */
		gds->HaveYear++;
		gds->HaveMonth++;
		gds->HaveDay++;
		gds->Month = gds->tokenp[0].value;
		gds->Day = gds->tokenp[1].value;
		gds->Year = gds->tokenp[3].value;
		gds->tokenp += 4;
		return 1;
	}

	if (gds->tokenp[0].token == tMONTH
	    && gds->tokenp[1].token == tUNUMBER) {
		/* "May 3" */
		gds->HaveMonth++;
		gds->HaveDay++;
		gds->Month = gds->tokenp[0].value;
		gds->Day = gds->tokenp[1].value;
		gds->tokenp += 2;
		return 1;
	}

	if (gds->tokenp[0].token == tUNUMBER
	    && gds->tokenp[1].token == tMONTH
	    && gds->tokenp[2].token == tUNUMBER) {
		/* "12 Sept 1997" */
		gds->HaveYear++;
		gds->HaveMonth++;
		gds->HaveDay++;
		gds->Day = gds->tokenp[0].value;
		gds->Month = gds->tokenp[1].value;
		gds->Year = gds->tokenp[2].value;
		gds->tokenp += 3;
		return 1;
	}

	if (gds->tokenp[0].token == tUNUMBER
	    && gds->tokenp[1].token == tMONTH) {
		/* "12 Sept" */
		gds->HaveMonth++;
		gds->HaveDay++;
		gds->Day = gds->tokenp[0].value;
		gds->Month = gds->tokenp[1].value;
		gds->tokenp += 2;
		return 1;
	}

	return 0;
}