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

long
Days ( int Year )		/* return number of days since year "0" */
{
    long  Return;
		/* this is a known to be good algorithm */
    Return = Year * 365;	/* first aproximation to the value */
    if ( Year >= 1 )
    {		/* see notes in libparse/parse.c if you want a PROPER
		 * **generic algorithm. */
	Return += (Year+3) / 4;		/* add in (too many) leap days */
	Return -= (Year-1) / 100;	/* reduce by (too many) centurys */
	Return += (Year-1) / 400;	/* get final answer */
    }

    return Return;
}