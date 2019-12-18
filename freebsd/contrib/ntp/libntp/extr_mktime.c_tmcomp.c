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
struct tm {int tm_year; int tm_mon; int tm_mday; int tm_isdst; int tm_hour; int tm_min; int tm_sec; } ;

/* Variables and functions */
 struct tm* mkdst (struct tm*) ; 

__attribute__((used)) static int
tmcomp(
	register struct tm * atmp,
	register struct tm * btmp
	)
{
	register int	result;

	/* compare down to the same day */

	if ((result = (atmp->tm_year - btmp->tm_year)) == 0 &&
	    (result = (atmp->tm_mon - btmp->tm_mon)) == 0)
	    result = (atmp->tm_mday - btmp->tm_mday);

	if(result != 0)
	    return result;

	/* get rid of one-sided dst bias */

	if(atmp->tm_isdst == 1 && !btmp->tm_isdst)
	    btmp = mkdst(btmp);
	else if(btmp->tm_isdst == 1 && !atmp->tm_isdst)
	    atmp = mkdst(atmp);

	/* compare the rest of the way */

	if ((result = (atmp->tm_hour - btmp->tm_hour)) == 0 &&
	    (result = (atmp->tm_min - btmp->tm_min)) == 0)
	    result = atmp->tm_sec - btmp->tm_sec;
	return result;
}