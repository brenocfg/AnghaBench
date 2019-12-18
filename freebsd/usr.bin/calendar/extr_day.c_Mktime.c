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
typedef  scalar_t__ time_t ;
struct tm {int tm_mday; int tm_mon; int tm_year; } ;

/* Variables and functions */
 char* asctime (struct tm*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,char*) ; 
 int /*<<< orphan*/  localtime_r (scalar_t__*,struct tm*) ; 
 scalar_t__ mktime (struct tm*) ; 
 int sscanf (char*,char*,int*,int*,int*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  time (scalar_t__*) ; 
 struct tm tm0 ; 

time_t
Mktime(char *dp)
{
	time_t t;
	int d, m, y;
	struct tm tm, tp;

	(void)time(&t);
	localtime_r(&t, &tp);

	tm = tm0;
	tm.tm_mday = tp.tm_mday;
	tm.tm_mon = tp.tm_mon;
	tm.tm_year = tp.tm_year;

	switch (sscanf(dp, "%d.%d.%d", &d, &m, &y)) {
	case 3:
		if (y > 1900)
			y -= 1900;
		tm.tm_year = y;
		/* FALLTHROUGH */
	case 2:
		tm.tm_mon = m - 1;
		/* FALLTHROUGH */
	case 1:
		tm.tm_mday = d;
	}

#ifdef DEBUG
	fprintf(stderr, "Mktime: %d %d %s\n",
	    (int)mktime(&tm), (int)t, asctime(&tm));
#endif
	return (mktime(&tm));
}