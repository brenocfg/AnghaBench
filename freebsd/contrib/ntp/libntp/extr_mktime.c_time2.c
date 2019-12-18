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
typedef  int time_t ;
struct tm {int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_year; int tm_mon; scalar_t__ tm_isdst; } ;

/* Variables and functions */
 int FALSE ; 
 int HOURSPERDAY ; 
 int MINSPERHOUR ; 
 int MONSPERYEAR ; 
 int SECSPERMIN ; 
 int TM_YEAR_BASE ; 
 int TRUE ; 
 int WRONG ; 
 struct tm* gmtime (int*) ; 
 size_t isleap (int) ; 
 struct tm* localtime (int*) ; 
 int** mon_lengths ; 
 int /*<<< orphan*/  normalize (int*,int*,int) ; 
 int tmcomp (struct tm*,struct tm*) ; 
 scalar_t__* year_lengths ; 

__attribute__((used)) static time_t
time2(
	struct tm *	tmp,
	int * 		okayp,
	int		usezn
	)
{
	register int			dir;
	register int			bits;
	register int			i;
	register int			saved_seconds;
	time_t				t;
	struct tm			yourtm, mytm;

	*okayp = FALSE;
	yourtm = *tmp;
	if (yourtm.tm_sec >= SECSPERMIN + 2 || yourtm.tm_sec < 0)
		normalize(&yourtm.tm_min, &yourtm.tm_sec, SECSPERMIN);
	normalize(&yourtm.tm_hour, &yourtm.tm_min, MINSPERHOUR);
	normalize(&yourtm.tm_mday, &yourtm.tm_hour, HOURSPERDAY);
	normalize(&yourtm.tm_year, &yourtm.tm_mon, MONSPERYEAR);
	while (yourtm.tm_mday <= 0) {
		--yourtm.tm_year;
		yourtm.tm_mday +=
			year_lengths[isleap(yourtm.tm_year + TM_YEAR_BASE)];
	}
	for ( ; ; ) {
		i = mon_lengths[isleap(yourtm.tm_year +
			TM_YEAR_BASE)][yourtm.tm_mon];
		if (yourtm.tm_mday <= i)
			break;
		yourtm.tm_mday -= i;
		if (++yourtm.tm_mon >= MONSPERYEAR) {
			yourtm.tm_mon = 0;
			++yourtm.tm_year;
		}
	}
	saved_seconds = yourtm.tm_sec;
	yourtm.tm_sec = 0;
	/*
	** Calculate the number of magnitude bits in a time_t
	** (this works regardless of whether time_t is
	** signed or unsigned, though lint complains if unsigned).
	*/
	for (bits = 0, t = 1; t > 0; ++bits, t <<= 1)
		;
	/*
	** If time_t is signed, then 0 is the median value,
	** if time_t is unsigned, then 1 << bits is median.
	*/
	t = (t < 0) ? 0 : ((time_t) 1 << bits);
	for ( ; ; ) {
		if (usezn)
			mytm = *localtime(&t);
		else
			mytm = *gmtime(&t);
		dir = tmcomp(&mytm, &yourtm);
		if (dir != 0) {
			if (bits-- < 0)
				return WRONG;
			if (bits < 0)
				--t;
			else if (dir > 0)
				t -= (time_t) 1 << bits;
			else	t += (time_t) 1 << bits;
			continue;
		}
		if (yourtm.tm_isdst < 0 || mytm.tm_isdst == yourtm.tm_isdst)
			break;

		return WRONG;
	}
	t += saved_seconds;
	if (usezn)
		*tmp = *localtime(&t);
	else
		*tmp = *gmtime(&t);
	*okayp = TRUE;
	return t;
}