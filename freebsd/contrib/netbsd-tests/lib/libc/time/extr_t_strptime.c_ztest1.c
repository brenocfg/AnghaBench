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
typedef  int /*<<< orphan*/  tm ;
struct tm {int tm_gmtoff; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,char const*,char const*,long,long) ; 
 int /*<<< orphan*/  memset (struct tm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char const*,char const*,long) ; 
 char* strptime (char const*,char const*,struct tm*) ; 
 long timezone ; 

__attribute__((used)) static void
ztest1(const char *name, const char *fmt, long value)
{
	struct tm tm;
	char *rv;

	memset(&tm, 0, sizeof(tm));
	if ((rv = strptime(name, fmt, &tm)) == NULL) 
		tm.tm_gmtoff = -1;
	else if (rv == name && fmt[1] == 'Z')
		value = 0;

	switch (value) {
#ifndef __FreeBSD__
	case -2:
		value = -timezone;
		break;
#endif
	case -1:
		if (fmt[1] == 'Z')
			value = 0;
		break;
	default:
		break;
	}

	ATF_REQUIRE_MSG(tm.tm_gmtoff == value,
	    "strptime(\"%s\", \"%s\", &tm): "
	    "expected: tm.tm_gmtoff=%ld, got: tm.tm_gmtoff=%ld",
	    name, fmt, value, tm.tm_gmtoff);
	printf("%s %s %ld\n", name, fmt, tm.tm_gmtoff);
}