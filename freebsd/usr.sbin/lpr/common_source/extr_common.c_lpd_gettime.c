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
struct timeval {int tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct timespec {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  LPD_TIMESTAMP_PATTERN ; 
 int TIMESTR_SIZE ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 scalar_t__ daylight ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct timespec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strftime (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 
 int timezone ; 

void
lpd_gettime(struct timespec *tsp, char *strp, size_t strsize)
{
	struct timespec local_ts;
	struct timeval btime;
	char tempstr[TIMESTR_SIZE];
#ifdef STRFTIME_WRONG_z
	char *destp;
#endif

	if (tsp == NULL)
		tsp = &local_ts;

	/* some platforms have a routine called clock_gettime, but the
	 * routine does nothing but return "not implemented". */
	memset(tsp, 0, sizeof(struct timespec));
	if (clock_gettime(CLOCK_REALTIME, tsp)) {
		/* nanosec-aware rtn failed, fall back to microsec-aware rtn */
		memset(tsp, 0, sizeof(struct timespec));
		gettimeofday(&btime, NULL);
		tsp->tv_sec = btime.tv_sec;
		tsp->tv_nsec = btime.tv_usec * 1000;
	}

	/* caller may not need a character-ized version */
	if ((strp == NULL) || (strsize < 1))
		return;

	strftime(tempstr, TIMESTR_SIZE, LPD_TIMESTAMP_PATTERN,
		 localtime(&tsp->tv_sec));

	/*
	 * This check is for implementations of strftime which treat %z
	 * (timezone as [+-]hhmm ) like %Z (timezone as characters), or
	 * completely ignore %z.  This section is not needed on freebsd.
	 * I'm not sure this is completely right, but it should work OK
	 * for EST and EDT...
	 */
#ifdef STRFTIME_WRONG_z
	destp = strrchr(tempstr, ':');
	if (destp != NULL) {
		destp += 3;
		if ((*destp != '+') && (*destp != '-')) {
			char savday[6];
			int tzmin = timezone / 60;
			int tzhr = tzmin / 60;
			if (daylight)
				tzhr--;
			strcpy(savday, destp + strlen(destp) - 4);
			snprintf(destp, (destp - tempstr), "%+03d%02d",
			    (-1*tzhr), tzmin % 60);
			strcat(destp, savday);
		}
	}
#endif

	if (strsize > TIMESTR_SIZE) {
		strsize = TIMESTR_SIZE;
		strp[TIMESTR_SIZE+1] = '\0';
	}
	strlcpy(strp, tempstr, strsize);
}