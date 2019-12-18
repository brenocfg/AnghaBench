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
struct tm {int tm_isdst; int /*<<< orphan*/  tm_sec; } ;
struct timespec {int /*<<< orphan*/  tv_sec; scalar_t__ tv_nsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ isdigit (unsigned char) ; 
 int /*<<< orphan*/  mktime (struct tm*) ; 
 char* strchr (char const*,char) ; 
 char* strptime (char const*,char const*,struct tm*) ; 
 int /*<<< orphan*/  timegm (struct tm*) ; 

__attribute__((used)) static void
stime_darg(const char *arg, struct timespec *tvp)
{
	struct tm t = { .tm_sec = 0 };
	const char *fmt, *colon;
	char *p;
	int val, isutc = 0;

	tvp[0].tv_nsec = 0;
	t.tm_isdst = -1;
	colon = strchr(arg, ':');
	if (colon == NULL || strchr(colon + 1, ':') == NULL)
		goto bad;
	fmt = strchr(arg, 'T') != NULL ? "%Y-%m-%dT%H:%M:%S" :
	    "%Y-%m-%d %H:%M:%S";
	p = strptime(arg, fmt, &t);
	if (p == NULL)
		goto bad;
	/* POSIX: must have at least one digit after dot */
	if ((*p == '.' || *p == ',') && isdigit((unsigned char)p[1])) {
		p++;
		val = 100000000;
		while (isdigit((unsigned char)*p)) {
			tvp[0].tv_nsec += val * (*p - '0');
			p++;
			val /= 10;
		}
	}
	if (*p == 'Z') {
		isutc = 1;
		p++;
	}
	if (*p != '\0')
		goto bad;

	tvp[0].tv_sec = isutc ? timegm(&t) : mktime(&t);

	tvp[1] = tvp[0];
	return;

bad:
	errx(1, "out of range or illegal time specification: YYYY-MM-DDThh:mm:SS[.frac][tz]");
}