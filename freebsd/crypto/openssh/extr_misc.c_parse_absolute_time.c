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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  tm ;
typedef  scalar_t__ time_t ;
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int SSH_ERR_INVALID_FORMAT ; 
 int /*<<< orphan*/  memset (struct tm*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mktime (struct tm*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*,char const*,...) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/ * strptime (char*,char*,struct tm*) ; 

int
parse_absolute_time(const char *s, uint64_t *tp)
{
	struct tm tm;
	time_t tt;
	char buf[32], *fmt;

	*tp = 0;

	/*
	 * POSIX strptime says "The application shall ensure that there
	 * is white-space or other non-alphanumeric characters between
	 * any two conversion specifications" so arrange things this way.
	 */
	switch (strlen(s)) {
	case 8: /* YYYYMMDD */
		fmt = "%Y-%m-%d";
		snprintf(buf, sizeof(buf), "%.4s-%.2s-%.2s", s, s + 4, s + 6);
		break;
	case 12: /* YYYYMMDDHHMM */
		fmt = "%Y-%m-%dT%H:%M";
		snprintf(buf, sizeof(buf), "%.4s-%.2s-%.2sT%.2s:%.2s",
		    s, s + 4, s + 6, s + 8, s + 10);
		break;
	case 14: /* YYYYMMDDHHMMSS */
		fmt = "%Y-%m-%dT%H:%M:%S";
		snprintf(buf, sizeof(buf), "%.4s-%.2s-%.2sT%.2s:%.2s:%.2s",
		    s, s + 4, s + 6, s + 8, s + 10, s + 12);
		break;
	default:
		return SSH_ERR_INVALID_FORMAT;
	}

	memset(&tm, 0, sizeof(tm));
	if (strptime(buf, fmt, &tm) == NULL)
		return SSH_ERR_INVALID_FORMAT;
	if ((tt = mktime(&tm)) < 0)
		return SSH_ERR_INVALID_FORMAT;
	/* success */
	*tp = (uint64_t)tt;
	return 0;
}