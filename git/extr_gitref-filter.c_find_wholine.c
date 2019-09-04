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
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,int) ; 

__attribute__((used)) static const char *find_wholine(const char *who, int wholen, const char *buf)
{
	const char *eol;
	while (*buf) {
		if (!strncmp(buf, who, wholen) &&
		    buf[wholen] == ' ')
			return buf + wholen + 1;
		eol = strchr(buf, '\n');
		if (!eol)
			return "";
		eol++;
		if (*eol == '\n')
			return ""; /* end of header */
		buf = eol;
	}
	return "";
}