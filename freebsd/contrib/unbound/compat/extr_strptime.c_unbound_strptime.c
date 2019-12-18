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
struct tm {int tm_wday; int tm_mon; int tm_year; int tm_mday; int tm_hour; int tm_yday; int tm_min; int tm_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  TM_YEAR_BASE ; 
 int /*<<< orphan*/  abb_months ; 
 int /*<<< orphan*/  abb_weekdays ; 
 int /*<<< orphan*/  ampm ; 
 int /*<<< orphan*/  full_months ; 
 int /*<<< orphan*/  full_weekdays ; 
 scalar_t__ isspace (unsigned char) ; 
 int match_string (char const**,int /*<<< orphan*/ ) ; 
 int str2int (char const**,int) ; 

char *
unbound_strptime(const char *s, const char *format, struct tm *tm)
{
	int c, ret;
	int split_year = 0;

	while ((c = *format) != '\0') {
		/* whitespace, literal or format */
		if (isspace((unsigned char)c)) { /* whitespace */
			/** whitespace matches zero or more whitespace characters in the
			  * input string.
			 **/
			while (isspace((unsigned char)*s))
				s++;
		}
		else if (c == '%') { /* format */
			format++;
			c = *format;
			switch (c) {
				case '%': /* %% is converted to % */
					if (*s != c) {
						return NULL;
					}
					s++;
					break;
				case 'a': /* weekday name, abbreviated or full */
				case 'A':
					ret = match_string(&s, full_weekdays);
					if (ret < 0)
						ret = match_string(&s, abb_weekdays);
					if (ret < 0) {
						return NULL;
					}
					tm->tm_wday = ret;
					break;
				case 'b': /* month name, abbreviated or full */
				case 'B':
				case 'h':
					ret = match_string(&s, full_months);
					if (ret < 0)
						ret = match_string(&s, abb_months);
					if (ret < 0) {
						return NULL;
					}
					tm->tm_mon = ret;
					break;
				case 'c': /* date and time representation */
					if (!(s = unbound_strptime(s, "%x %X", tm))) {
						return NULL;
					}
					break;
				case 'C': /* century number */
					ret = str2int(&s, 2);
					if (ret < 0 || ret > 99) { /* must be in [00,99] */
						return NULL;
					}

					if (split_year)	{
						tm->tm_year = ret*100 + (tm->tm_year%100);
					}
					else {
						tm->tm_year = ret*100 - TM_YEAR_BASE;
						split_year = 1;
					}
					break;
				case 'd': /* day of month */
				case 'e':
					ret = str2int(&s, 2);
					if (ret < 1 || ret > 31) { /* must be in [01,31] */
						return NULL;
					}
					tm->tm_mday = ret;
					break;
				case 'D': /* equivalent to %m/%d/%y */
					if (!(s = unbound_strptime(s, "%m/%d/%y", tm))) {
						return NULL;
					}
					break;
				case 'H': /* hour */
					ret = str2int(&s, 2);
					if (ret < 0 || ret > 23) { /* must be in [00,23] */
						return NULL;
					}
					tm->tm_hour = ret;
					break;
				case 'I': /* 12hr clock hour */
					ret = str2int(&s, 2);
					if (ret < 1 || ret > 12) { /* must be in [01,12] */
						return NULL;
					}
					if (ret == 12) /* actually [0,11] */
						ret = 0;
					tm->tm_hour = ret;
					break;
				case 'j': /* day of year */
					ret = str2int(&s, 2);
					if (ret < 1 || ret > 366) { /* must be in [001,366] */
						return NULL;
					}
					tm->tm_yday = ret;
					break;
				case 'm': /* month */
					ret = str2int(&s, 2);
					if (ret < 1 || ret > 12) { /* must be in [01,12] */
						return NULL;
					}
					/* months go from 0-11 */
					tm->tm_mon = (ret-1);
					break;
				case 'M': /* minute */
					ret = str2int(&s, 2);
					if (ret < 0 || ret > 59) { /* must be in [00,59] */
						return NULL;
					}
					tm->tm_min = ret;
					break;
				case 'n': /* arbitrary whitespace */
				case 't':
					while (isspace((unsigned char)*s))
						s++;
					break;
				case 'p': /* am pm */
					ret = match_string(&s, ampm);
					if (ret < 0) {
						return NULL;
					}
					if (tm->tm_hour < 0 || tm->tm_hour > 11) { /* %I */
						return NULL;
					}

					if (ret == 1) /* pm */
						tm->tm_hour += 12;
					break;
				case 'r': /* equivalent of %I:%M:%S %p */
					if (!(s = unbound_strptime(s, "%I:%M:%S %p", tm))) {
						return NULL;
					}
					break;
				case 'R': /* equivalent of %H:%M */
					if (!(s = unbound_strptime(s, "%H:%M", tm))) {
						return NULL;
					}
					break;
				case 'S': /* seconds */
					ret = str2int(&s, 2);
					/* 60 may occur for leap seconds */
					/* earlier 61 was also allowed */
					if (ret < 0 || ret > 60) { /* must be in [00,60] */
						return NULL;
					}
					tm->tm_sec = ret;
					break;
				case 'T': /* equivalent of %H:%M:%S */
					if (!(s = unbound_strptime(s, "%H:%M:%S", tm))) {
						return NULL;
					}
					break;
				case 'U': /* week number, with the first Sun of Jan being w1 */
					ret = str2int(&s, 2);
					if (ret < 0 || ret > 53) { /* must be in [00,53] */
						return NULL;
					}
					/** it is hard (and not necessary for nsd) to determine time
					  * data from week number.
					 **/
					break;
				case 'w': /* day of week */
					ret = str2int(&s, 1);
					if (ret < 0 || ret > 6) { /* must be in [0,6] */
						return NULL;
					}
					tm->tm_wday = ret;
					break;
				case 'W': /* week number, with the first Mon of Jan being w1 */
					ret = str2int(&s, 2);
					if (ret < 0 || ret > 53) { /* must be in [00,53] */
						return NULL;
					}
					/** it is hard (and not necessary for nsd) to determine time
					  * data from week number.
					 **/
					break;
				case 'x': /* date format */
					if (!(s = unbound_strptime(s, "%m/%d/%y", tm))) {
						return NULL;
					}
					break;
				case 'X': /* time format */
					if (!(s = unbound_strptime(s, "%H:%M:%S", tm))) {
						return NULL;
					}
					break;
				case 'y': /* last two digits of a year */
					ret = str2int(&s, 2);
					if (ret < 0 || ret > 99) { /* must be in [00,99] */
						return NULL;
					}
					if (split_year) {
						tm->tm_year = ((tm->tm_year/100) * 100) + ret;
					}
					else {
						split_year = 1;

						/** currently:
						  * if in [0,68] we are in 21th century,
						  * if in [69,99] we are in 20th century.
						 **/
						if (ret < 69) /* 2000 */
							ret += 100;
						tm->tm_year = ret;
					}
					break;
				case 'Y': /* year */
					ret = str2int(&s, 4);
					if (ret < 0 || ret > 9999) {
						return NULL;
					}
					tm->tm_year = ret - TM_YEAR_BASE;
					break;
				case '\0':
				default: /* unsupported, cannot match format */
					return NULL;
					break;
			}
		}
		else { /* literal */
			/* if input cannot match format, return NULL */
			if (*s != c)
				return NULL;
			s++;
		}

		format++;
	}

	/* return pointer to remainder of s */
	return (char*) s;
}