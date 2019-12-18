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

/* Variables and functions */
 scalar_t__ CHAR_IS_UNRESERVED (char const) ; 
 scalar_t__ EVUTIL_ISXDIGIT_ (char const) ; 
 int /*<<< orphan*/  SUBDELIMS ; 
 scalar_t__ strchr (int /*<<< orphan*/ ,char const) ; 

__attribute__((used)) static int
userinfo_ok(const char *s, const char *eos)
{
	while (s < eos) {
		if (CHAR_IS_UNRESERVED(*s) ||
		    strchr(SUBDELIMS, *s) ||
		    *s == ':')
			++s;
		else if (*s == '%' && s+2 < eos &&
		    EVUTIL_ISXDIGIT_(s[1]) &&
		    EVUTIL_ISXDIGIT_(s[2]))
			s += 3;
		else
			return 0;
	}
	return 1;
}