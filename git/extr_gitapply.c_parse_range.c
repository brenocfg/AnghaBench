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
 scalar_t__ memcmp (char const*,char const*,int) ; 
 int parse_num (char const*,unsigned long*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int parse_range(const char *line, int len, int offset, const char *expect,
		       unsigned long *p1, unsigned long *p2)
{
	int digits, ex;

	if (offset < 0 || offset >= len)
		return -1;
	line += offset;
	len -= offset;

	digits = parse_num(line, p1);
	if (!digits)
		return -1;

	offset += digits;
	line += digits;
	len -= digits;

	*p2 = 1;
	if (*line == ',') {
		digits = parse_num(line+1, p2);
		if (!digits)
			return -1;

		offset += digits+1;
		line += digits+1;
		len -= digits+1;
	}

	ex = strlen(expect);
	if (ex > len)
		return -1;
	if (memcmp(line, expect, ex))
		return -1;

	return offset + ex;
}