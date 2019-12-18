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
struct TYPE_2__ {scalar_t__ tm_isdst; } ;
struct ptime_data {scalar_t__ did_adj4dst; TYPE_1__ tm; int /*<<< orphan*/  tsecs; } ;

/* Variables and functions */
 scalar_t__ SECS_PER_HOUR ; 
 scalar_t__ TNYET_ADJ4DST ; 
 TYPE_1__* localtime (int /*<<< orphan*/ *) ; 

int
ptime_adjust4dst(struct ptime_data *ptime, const struct ptime_data *dstsrc)
{
	struct ptime_data adjtime;

	if (ptime == NULL)
		return (-1);

	/*
	 * Changes are not made to the given time until after all
	 * of the calculations have been successful.
	 */
	adjtime = *ptime;

	/* Check to see if this adjustment was already made */
	if ((adjtime.did_adj4dst != TNYET_ADJ4DST) &&
	    (adjtime.did_adj4dst == dstsrc->tm.tm_isdst))
		return (0);		/* yes, so don't make it twice */

	/* See if daylight-saving has changed between the two times. */
	if (dstsrc->tm.tm_isdst != adjtime.tm.tm_isdst) {
		if (adjtime.tm.tm_isdst == 1)
			adjtime.tsecs -= SECS_PER_HOUR;
		else if (adjtime.tm.tm_isdst == 0)
			adjtime.tsecs += SECS_PER_HOUR;
		adjtime.tm = *(localtime(&adjtime.tsecs));
		/* Remember that this adjustment has been made */
		adjtime.did_adj4dst = dstsrc->tm.tm_isdst;
		/*
		 * XXX - Should probably check to see if changing the
		 *	hour also changed the value of is_dst.  What
		 *	should we do in that case?
		 */
	}

	*ptime = adjtime;
	return (0);
}