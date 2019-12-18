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
struct tm {int tm_wday; int tm_mon; int tm_mday; int tm_hour; int tm_yday; int tm_min; int tm_sec; int tm_year; } ;

/* Variables and functions */
 int TM_YEAR_BASE ; 
 int _ALT_E ; 
 int _ALT_O ; 
 int /*<<< orphan*/  _LEGAL_ALT (int) ; 
 int /*<<< orphan*/  _conv_num (unsigned char const**,int*,int,int) ; 
 char* _ctloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * abday ; 
 int /*<<< orphan*/ * abmon ; 
 int /*<<< orphan*/ * am_pm ; 
 int /*<<< orphan*/  d_fmt ; 
 int /*<<< orphan*/  d_t_fmt ; 
 int /*<<< orphan*/ * day ; 
 scalar_t__ isspace (unsigned char const) ; 
 int /*<<< orphan*/ * mon ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strncasecmp (char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  t_fmt ; 

__attribute__((used)) static char *
_strptime(const char *buf, const char *fmt, struct tm *tm, int initialize)
{
	unsigned char c;
	const unsigned char *bp;
	size_t len;
	int alt_format, i;
	static int century, relyear;

	if (initialize) {
		century = TM_YEAR_BASE;
		relyear = -1;
	}

	bp = (unsigned char *)buf;
	while ((c = *fmt) != '\0') {
		/* Clear `alternate' modifier prior to new conversion. */
		alt_format = 0;

		/* Eat up white-space. */
		if (isspace(c)) {
			while (isspace(*bp))
				bp++;

			fmt++;
			continue;
		}
				
		if ((c = *fmt++) != '%')
			goto literal;


again:		switch (c = *fmt++) {
		case '%':	/* "%%" is converted to "%". */
literal:
		if (c != *bp++)
			return (NULL);

		break;

		/*
		 * "Alternative" modifiers. Just set the appropriate flag
		 * and start over again.
		 */
		case 'E':	/* "%E?" alternative conversion modifier. */
			_LEGAL_ALT(0);
			alt_format |= _ALT_E;
			goto again;

		case 'O':	/* "%O?" alternative conversion modifier. */
			_LEGAL_ALT(0);
			alt_format |= _ALT_O;
			goto again;
			
		/*
		 * "Complex" conversion rules, implemented through recursion.
		 */
#if 0
		case 'c':	/* Date and time, using the locale's format. */
			_LEGAL_ALT(_ALT_E);
			if (!(bp = _strptime(bp, _ctloc(d_t_fmt), tm, 0)))
				return (NULL);
			break;
#endif
		case 'D':	/* The date as "%m/%d/%y". */
			_LEGAL_ALT(0);
			if (!(bp = _strptime(bp, "%m/%d/%y", tm, 0)))
				return (NULL);
			break;
	
		case 'R':	/* The time as "%H:%M". */
			_LEGAL_ALT(0);
			if (!(bp = _strptime(bp, "%H:%M", tm, 0)))
				return (NULL);
			break;

		case 'r':	/* The time as "%I:%M:%S %p". */
			_LEGAL_ALT(0);
			if (!(bp = _strptime(bp, "%I:%M:%S %p", tm, 0)))
				return (NULL);
			break;

		case 'T':	/* The time as "%H:%M:%S". */
			_LEGAL_ALT(0);
			if (!(bp = _strptime(bp, "%H:%M:%S", tm, 0)))
				return (NULL);
			break;
#if 0
		case 'X':	/* The time, using the locale's format. */
			_LEGAL_ALT(_ALT_E);
			if (!(bp = _strptime(bp, _ctloc(t_fmt), tm, 0)))
				return (NULL);
			break;

		case 'x':	/* The date, using the locale's format. */
			_LEGAL_ALT(_ALT_E);
			if (!(bp = _strptime(bp, _ctloc(d_fmt), tm, 0)))
				return (NULL);
			break;
#endif
		/*
		 * "Elementary" conversion rules.
		 */
#if 0
		case 'A':	/* The day of week, using the locale's form. */
		case 'a':
			_LEGAL_ALT(0);
			for (i = 0; i < 7; i++) {
				/* Full name. */
				len = strlen(_ctloc(day[i]));
				if (strncasecmp(_ctloc(day[i]), bp, len) == 0)
					break;

				/* Abbreviated name. */
				len = strlen(_ctloc(abday[i]));
				if (strncasecmp(_ctloc(abday[i]), bp, len) == 0)
					break;
			}

			/* Nothing matched. */
			if (i == 7)
				return (NULL);

			tm->tm_wday = i;
			bp += len;
			break;

		case 'B':	/* The month, using the locale's form. */
		case 'b':
		case 'h':
			_LEGAL_ALT(0);
			for (i = 0; i < 12; i++) {
				/* Full name. */
				len = strlen(_ctloc(mon[i]));
				if (strncasecmp(_ctloc(mon[i]), bp, len) == 0)
					break;

				/* Abbreviated name. */
				len = strlen(_ctloc(abmon[i]));
				if (strncasecmp(_ctloc(abmon[i]), bp, len) == 0)
					break;
			}

			/* Nothing matched. */
			if (i == 12)
				return (NULL);

			tm->tm_mon = i;
			bp += len;
			break;
#endif

		case 'C':	/* The century number. */
			_LEGAL_ALT(_ALT_E);
			if (!(_conv_num(&bp, &i, 0, 99)))
				return (NULL);

			century = i * 100;
			break;

		case 'd':	/* The day of month. */
		case 'e':
			_LEGAL_ALT(_ALT_O);
			if (!(_conv_num(&bp, &tm->tm_mday, 1, 31)))
				return (NULL);
			break;

		case 'k':	/* The hour (24-hour clock representation). */
			_LEGAL_ALT(0);
			/* FALLTHROUGH */
		case 'H':
			_LEGAL_ALT(_ALT_O);
			if (!(_conv_num(&bp, &tm->tm_hour, 0, 23)))
				return (NULL);
			break;

		case 'l':	/* The hour (12-hour clock representation). */
			_LEGAL_ALT(0);
			/* FALLTHROUGH */
		case 'I':
			_LEGAL_ALT(_ALT_O);
			if (!(_conv_num(&bp, &tm->tm_hour, 1, 12)))
				return (NULL);
			break;

		case 'j':	/* The day of year. */
			_LEGAL_ALT(0);
			if (!(_conv_num(&bp, &tm->tm_yday, 1, 366)))
				return (NULL);
			tm->tm_yday--;
			break;

		case 'M':	/* The minute. */
			_LEGAL_ALT(_ALT_O);
			if (!(_conv_num(&bp, &tm->tm_min, 0, 59)))
				return (NULL);
			break;

		case 'm':	/* The month. */
			_LEGAL_ALT(_ALT_O);
			if (!(_conv_num(&bp, &tm->tm_mon, 1, 12)))
				return (NULL);
			tm->tm_mon--;
			break;

#if 0
		case 'p':	/* The locale's equivalent of AM/PM. */
			_LEGAL_ALT(0);
			/* AM? */
			len = strlen(_ctloc(am_pm[0]));
			if (strncasecmp(_ctloc(am_pm[0]), bp, len) == 0) {
				if (tm->tm_hour > 12)	/* i.e., 13:00 AM ?! */
					return (NULL);
				else if (tm->tm_hour == 12)
					tm->tm_hour = 0;

				bp += len;
				break;
			}
			/* PM? */
			len = strlen(_ctloc(am_pm[1]));
			if (strncasecmp(_ctloc(am_pm[1]), bp, len) == 0) {
				if (tm->tm_hour > 12)	/* i.e., 13:00 PM ?! */
					return (NULL);
				else if (tm->tm_hour < 12)
					tm->tm_hour += 12;

				bp += len;
				break;
			}

			/* Nothing matched. */
			return (NULL);
#endif
		case 'S':	/* The seconds. */
			_LEGAL_ALT(_ALT_O);
			if (!(_conv_num(&bp, &tm->tm_sec, 0, 61)))
				return (NULL);
			break;

		case 'U':	/* The week of year, beginning on sunday. */
		case 'W':	/* The week of year, beginning on monday. */
			_LEGAL_ALT(_ALT_O);
			/*
			 * XXX This is bogus, as we can not assume any valid
			 * information present in the tm structure at this
			 * point to calculate a real value, so just check the
			 * range for now.
			 */
			 if (!(_conv_num(&bp, &i, 0, 53)))
				return (NULL);
			 break;

		case 'w':	/* The day of week, beginning on sunday. */
			_LEGAL_ALT(_ALT_O);
			if (!(_conv_num(&bp, &tm->tm_wday, 0, 6)))
				return (NULL);
			break;

		case 'Y':	/* The year. */
			_LEGAL_ALT(_ALT_E);
			if (!(_conv_num(&bp, &i, 0, 9999)))
				return (NULL);

			relyear = -1;
			tm->tm_year = i - TM_YEAR_BASE;
			break;

		case 'y':	/* The year within the century (2 digits). */
			_LEGAL_ALT(_ALT_E | _ALT_O);
			if (!(_conv_num(&bp, &relyear, 0, 99)))
				return (NULL);
			break;

		/*
		 * Miscellaneous conversions.
		 */
		case 'n':	/* Any kind of white-space. */
		case 't':
			_LEGAL_ALT(0);
			while (isspace(*bp))
				bp++;
			break;


		default:	/* Unknown/unsupported conversion. */
			return (NULL);
		}


	}

	/*
	 * We need to evaluate the two digit year spec (%y)
	 * last as we can get a century spec (%C) at any time.
	 */
	if (relyear != -1) {
		if (century == TM_YEAR_BASE) {
			if (relyear <= 68)
				tm->tm_year = relyear + 2000 - TM_YEAR_BASE;
			else
				tm->tm_year = relyear + 1900 - TM_YEAR_BASE;
		} else {
			tm->tm_year = relyear + century - TM_YEAR_BASE;
		}
	}

	return ((char *)bp);
}