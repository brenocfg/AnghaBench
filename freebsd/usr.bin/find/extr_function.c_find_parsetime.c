#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ PLAN ;

/* Variables and functions */
 int /*<<< orphan*/  F_EQUAL ; 
 int /*<<< orphan*/  F_EXACTTIME ; 
 int /*<<< orphan*/  F_GREATER ; 
 int /*<<< orphan*/  F_LESSTHAN ; 
 int /*<<< orphan*/  errx (int,char*,char const*,char*,...) ; 
 long long strtoq (char*,char**,int) ; 

__attribute__((used)) static long long
find_parsetime(PLAN *plan, const char *option, char *vp)
{
	long long secs, value;
	char *str, *unit;	/* Pointer to character ending conversion. */

	/* Determine comparison from leading + or -. */
	str = vp;
	switch (*str) {
	case '+':
		++str;
		plan->flags |= F_GREATER;
		break;
	case '-':
		++str;
		plan->flags |= F_LESSTHAN;
		break;
	default:
		plan->flags |= F_EQUAL;
		break;
	}

	value = strtoq(str, &unit, 10);
	if (value == 0 && unit == str) {
		errx(1, "%s: %s: illegal time value", option, vp);
		/* NOTREACHED */
	}
	if (*unit == '\0')
		return value;

	/* Units syntax. */
	secs = 0;
	for (;;) {
		switch(*unit) {
		case 's':	/* seconds */
			secs += value;
			break;
		case 'm':	/* minutes */
			secs += value * 60;
			break;
		case 'h':	/* hours */
			secs += value * 3600;
			break;
		case 'd':	/* days */
			secs += value * 86400;
			break;
		case 'w':	/* weeks */
			secs += value * 604800;
			break;
		default:
			errx(1, "%s: %s: bad unit '%c'", option, vp, *unit);
			/* NOTREACHED */
		}
		str = unit + 1;
		if (*str == '\0')	/* EOS */
			break;
		value = strtoq(str, &unit, 10);
		if (value == 0 && unit == str) {
			errx(1, "%s: %s: illegal time value", option, vp);
			/* NOTREACHED */
		}
		if (*unit == '\0') {
			errx(1, "%s: %s: missing trailing unit", option, vp);
			/* NOTREACHED */
		}
	}
	plan->flags |= F_EXACTTIME;
	return secs;
}