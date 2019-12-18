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
 char* strchr (char*,char) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int strtol (char*,char**,int) ; 

__attribute__((used)) static int
kfib_parse_opts(int *pfib, char *data)
{
	char *pdel, *pend, *s;
	int fibnum;

	if (data == NULL)
		return (0);
	if ((pdel = strchr(data, ' ')) == NULL)
		return (0);
	while (*pdel == ' ')
		pdel++;
	if (strncmp(pdel, "fib=", 4) != 0)
		return (EINVAL);
	if ((s = strchr(pdel, ' ')) != NULL)
		*s++ = '\0';

	pdel += 4;
	/* Need \d+ */
	fibnum = strtol(pdel, &pend, 10);
	if (*pend != '\0')
		return (EINVAL);

	*pfib = fibnum;

	return (0);
}