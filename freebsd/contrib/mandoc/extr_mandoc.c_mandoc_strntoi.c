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
 long INT_MAX ; 
 long INT_MIN ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 long strtol (char*,char**,int) ; 

int
mandoc_strntoi(const char *p, size_t sz, int base)
{
	char		 buf[32];
	char		*ep;
	long		 v;

	if (sz > 31)
		return -1;

	memcpy(buf, p, sz);
	buf[(int)sz] = '\0';

	errno = 0;
	v = strtol(buf, &ep, base);

	if (buf[0] == '\0' || *ep != '\0')
		return -1;

	if (v > INT_MAX)
		v = INT_MAX;
	if (v < INT_MIN)
		v = INT_MIN;

	return (int)v;
}