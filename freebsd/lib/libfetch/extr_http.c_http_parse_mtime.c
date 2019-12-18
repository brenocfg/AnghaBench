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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; scalar_t__ tm_mon; scalar_t__ tm_year; } ;
typedef  int /*<<< orphan*/  locale ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGF (char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LC_TIME ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 char* strptime (char const*,char*,struct tm*) ; 
 int /*<<< orphan*/  timegm (struct tm*) ; 

__attribute__((used)) static int
http_parse_mtime(const char *p, time_t *mtime)
{
	char locale[64], *r;
	struct tm tm;

	strlcpy(locale, setlocale(LC_TIME, NULL), sizeof(locale));
	setlocale(LC_TIME, "C");
	r = strptime(p, "%a, %d %b %Y %H:%M:%S GMT", &tm);
	/*
	 * Some proxies use UTC in response, but it should still be
	 * parsed. RFC2616 states GMT and UTC are exactly equal for HTTP.
	 */
	if (r == NULL)
		r = strptime(p, "%a, %d %b %Y %H:%M:%S UTC", &tm);
	/* XXX should add support for date-2 and date-3 */
	setlocale(LC_TIME, locale);
	if (r == NULL)
		return (-1);
	DEBUGF("last modified: [%04d-%02d-%02d %02d:%02d:%02d]\n",
	    tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
	    tm.tm_hour, tm.tm_min, tm.tm_sec);
	*mtime = timegm(&tm);
	return (0);
}