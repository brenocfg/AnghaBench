#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tm ;
struct tm {int tm_mon; } ;
struct monthlines {char** lines; int* extralen; int /*<<< orphan*/ * name; } ;
struct TYPE_4__ {int y; int m; int d; } ;
typedef  TYPE_1__ date ;

/* Variables and functions */
 char* daystr ; 
 int /*<<< orphan*/  flag_nohighlight ; 
 int /*<<< orphan*/  highlight (char*,char*,int,int*) ; 
 int highlightdate ; 
 char* jdaystr ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (struct tm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdateb (int,TYPE_1__*) ; 
 int sndaysb (TYPE_1__*) ; 
 int /*<<< orphan*/  towupper (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcsftime (int /*<<< orphan*/ *,int,char*,struct tm*) ; 
 int weekday (int) ; 

__attribute__((used)) static void
mkmonthb(int y, int m, int jd_flag, struct monthlines *mlines)
{

	struct tm tm;		/* for strftime printing local names of
				 * months */
	date    dt;		/* handy date */
	int     dw;		/* width of numbers */
	int     first;		/* first day of month */
	int     firsts;		/* sunday of first week of month */
	int     i, j, k, l;	/* just indices */
	int     jan1 = 0;	/* the first day of this year */
	int     last;		/* the first day of next month */
	char   *ds;		/* pointer to day strings (daystr or
				 * jdaystr) */

	/* Set ds (daystring) and dw (daywidth) according to the jd_flag */
	if (jd_flag) {
		ds = jdaystr;
		dw = 4;
	} else {
		ds = daystr;
		dw = 3;
	}

	/* Set name of month centered. */
	memset(&tm, 0, sizeof(tm));
	tm.tm_mon = m;
	wcsftime(mlines->name, sizeof(mlines->name) / sizeof(mlines->name[0]),
		 L"%OB", &tm);
	mlines->name[0] = towupper(mlines->name[0]);

	/*
	 * Set first and last to the day number of the first day of this
	 * month and the first day of next month respectively. Set jan1 to
	 * the day number of Jan 1st of this year.
	 */
	dt.y = y;
	dt.m = m + 1;
	dt.d = 1;
	first = sndaysb(&dt);
	if (m == 11) {
		dt.y = y + 1;
		dt.m = 1;
		dt.d = 1;
	} else {
		dt.y = y;
		dt.m = m + 2;
		dt.d = 1;
	}
	last = sndaysb(&dt);

	if (jd_flag) {
		dt.y = y;
		dt.m = 1;
		dt.d = 1;
		jan1 = sndaysb(&dt);
	}

	/*
	 * Set firsts to the day number of sunday of the first week of
	 * this month. (This might be in the last month)
	 */
	firsts = first - (weekday(first)+1) % 7;

	/*
	 * Fill the lines with day of month or day of year (Julian day)
	 * line index: i, each line is one week. column index: j, each
	 * column is one day number. print column index: k.
	 */
	for (i = 0; i != 6; i++) {
		l = 0;
		for (j = firsts + 7 * i, k = 0; j < last && k != dw * 7;
		    j++, k += dw) { 
			if (j >= first) {
				if (jd_flag)
					dt.d = j - jan1 + 1;
				else
					sdateb(j, &dt);
				if (j == highlightdate && !flag_nohighlight)
					highlight(mlines->lines[i] + k,
					    ds + dt.d * dw, dw, &l);
				else
					memcpy(mlines->lines[i] + k + l,
					       ds + dt.d * dw, dw);
			} else
				memcpy(mlines->lines[i] + k + l, "    ", dw);
		}
		if (k == 0)
			mlines->lines[i][1] = '\0';
		else
			mlines->lines[i][k + l] = '\0';
		mlines->extralen[i] = l;
	}
}