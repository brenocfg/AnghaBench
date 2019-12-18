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
 int /*<<< orphan*/  EVUTIL_ISDIGIT_ (char const) ; 

__attribute__((used)) static int
parse_port(const char *s, const char *eos)
{
	int portnum = 0;
	while (s < eos) {
		if (! EVUTIL_ISDIGIT_(*s))
			return -1;
		portnum = (portnum * 10) + (*s - '0');
		if (portnum < 0)
			return -1;
		if (portnum > 65535)
			return -1;
		++s;
	}
	return portnum;
}