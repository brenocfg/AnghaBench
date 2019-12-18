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
 int /*<<< orphan*/  INT_MAX ; 
 long long strtonum (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 

const char *
atoi_err(const char *nptr, int *val)
{
	const char *errstr = NULL;
	long long num;

	if (nptr == NULL || *nptr == '\0')
		return "missing";
	num = strtonum(nptr, 0, INT_MAX, &errstr);
	if (errstr == NULL)
		*val = (int)num;
	return errstr;
}