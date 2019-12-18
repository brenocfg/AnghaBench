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
typedef  void* u_short ;
typedef  void* u_char ;
struct calendar {int monthday; int year; int hour; int minute; int second; void* month; scalar_t__ yearday; } ;
struct TYPE_4__ {scalar_t__ l_uf; int /*<<< orphan*/  l_ui; } ;
typedef  TYPE_1__ l_fp ;

/* Variables and functions */
 int /*<<< orphan*/  L_CLR (TYPE_1__*) ; 
 scalar_t__ STREQ (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caltontp (struct calendar*) ; 
 scalar_t__ isdigit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * months ; 
 int /*<<< orphan*/  pgetc (char*) ; 

__attribute__((used)) static int
rtdatetolfp(
	char *str,
	l_fp *lfp
	)
{
	register char *cp;
	register int i;
	struct calendar cal;
	char buf[4];

	cal.yearday = 0;

	/*
	 * An RT-11 date looks like:
	 *
	 * d[d]-Mth-y[y] hh:mm:ss
	 *
	 * (No docs, but assume 4-digit years are also legal...)
	 *
	 * d[d]-Mth-y[y[y[y]]] hh:mm:ss
	 */
	cp = str;
	if (!isdigit(pgetc(cp))) {
		if (*cp == '-') {
			/*
			 * Catch special case
			 */
			L_CLR(lfp);
			return 1;
		}
		return 0;
	}

	cal.monthday = (u_char) (*cp++ - '0');	/* ascii dependent */
	if (isdigit(pgetc(cp))) {
		cal.monthday = (u_char)((cal.monthday << 3) + (cal.monthday << 1));
		cal.monthday = (u_char)(cal.monthday + *cp++ - '0');
	}

	if (*cp++ != '-')
	    return 0;

	for (i = 0; i < 3; i++)
	    buf[i] = *cp++;
	buf[3] = '\0';

	for (i = 0; i < 12; i++)
	    if (STREQ(buf, months[i]))
		break;
	if (i == 12)
	    return 0;
	cal.month = (u_char)(i + 1);

	if (*cp++ != '-')
	    return 0;

	if (!isdigit(pgetc(cp)))
	    return 0;
	cal.year = (u_short)(*cp++ - '0');
	if (isdigit(pgetc(cp))) {
		cal.year = (u_short)((cal.year << 3) + (cal.year << 1));
		cal.year = (u_short)(*cp++ - '0');
	}
	if (isdigit(pgetc(cp))) {
		cal.year = (u_short)((cal.year << 3) + (cal.year << 1));
		cal.year = (u_short)(cal.year + *cp++ - '0');
	}
	if (isdigit(pgetc(cp))) {
		cal.year = (u_short)((cal.year << 3) + (cal.year << 1));
		cal.year = (u_short)(cal.year + *cp++ - '0');
	}

	/*
	 * Catch special case.  If cal.year == 0 this is a zero timestamp.
	 */
	if (cal.year == 0) {
		L_CLR(lfp);
		return 1;
	}

	if (*cp++ != ' ' || !isdigit(pgetc(cp)))
	    return 0;
	cal.hour = (u_char)(*cp++ - '0');
	if (isdigit(pgetc(cp))) {
		cal.hour = (u_char)((cal.hour << 3) + (cal.hour << 1));
		cal.hour = (u_char)(cal.hour + *cp++ - '0');
	}

	if (*cp++ != ':' || !isdigit(pgetc(cp)))
	    return 0;
	cal.minute = (u_char)(*cp++ - '0');
	if (isdigit(pgetc(cp))) {
		cal.minute = (u_char)((cal.minute << 3) + (cal.minute << 1));
		cal.minute = (u_char)(cal.minute + *cp++ - '0');
	}

	if (*cp++ != ':' || !isdigit(pgetc(cp)))
	    return 0;
	cal.second = (u_char)(*cp++ - '0');
	if (isdigit(pgetc(cp))) {
		cal.second = (u_char)((cal.second << 3) + (cal.second << 1));
		cal.second = (u_char)(cal.second + *cp++ - '0');
	}

	/*
	 * For RT-11, 1972 seems to be the pivot year
	 */
	if (cal.year < 72)
		cal.year += 2000;
	if (cal.year < 100)
		cal.year += 1900;

	lfp->l_ui = caltontp(&cal);
	lfp->l_uf = 0;
	return 1;
}