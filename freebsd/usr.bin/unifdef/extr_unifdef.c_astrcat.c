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
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ malloc (size_t) ; 
 int snprintf (char*,size_t,char*,char const*,char const*) ; 

__attribute__((used)) static char *
astrcat(const char *s1, const char *s2)
{
	char *s;
	int len;
	size_t size;

	len = snprintf(NULL, 0, "%s%s", s1, s2);
	if (len < 0)
		err(2, "snprintf");
	size = (size_t)len + 1;
	s = (char *)malloc(size);
	if (s == NULL)
		err(2, "malloc");
	snprintf(s, size, "%s%s", s1, s2);
	return (s);
}