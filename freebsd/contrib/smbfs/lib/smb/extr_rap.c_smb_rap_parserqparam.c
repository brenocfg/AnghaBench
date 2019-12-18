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
 int EINVAL ; 
 scalar_t__ isdigit (char const) ; 
 int strtoul (char const*,char**,int) ; 

__attribute__((used)) static int
smb_rap_parserqparam(const char *s, char **next, int *rlen)
{
	char *np;
	int len, m;

	m = 1;
	switch (*s++) {
	    case 'L':
	    case 'T':
	    case 'W':
		len = 2;
		break;
	    case 'D':
	    case 'O':
		len = 4;
		break;
	    case 'b':
	    case 'F':
		len = 1;
		break;
	    case 'r':
	    case 's':
		len = 0;
		break;
	    default:
		return EINVAL;
	}
	if (isdigit(*s)) {
		len *= strtoul(s, &np, 10);
		s = np;
	}
	*rlen = len;
	*(const char**)next = s;
	return 0;
}