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
typedef  int intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static int
numfromstr(const char *str, intmax_t minnum, intmax_t maxnum, intmax_t *nump)
{
	intmax_t digit, num;

	if (str[0] == '\0')
		goto invalid;	/* Empty string. */
	num = 0;
	for (; *str != '\0'; str++) {
		if (*str < '0' || *str > '9')
			goto invalid;	/* Non-digit character. */
		digit = *str - '0';
		if (num > num * 10 + digit)
			goto invalid;	/* Overflow. */
		num = num * 10 + digit;
		if (num > maxnum)
			goto invalid;	/* Too big. */
	}
	if (num < minnum)
		goto invalid;	/* Too small. */
	*nump = num;
	return (0);
invalid:
	errno = EINVAL;
	return (-1);
}