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
 scalar_t__ INT_MAX ; 
 scalar_t__ INT_MIN ; 
 scalar_t__ LONG_MAX ; 
 scalar_t__ LONG_MIN ; 
 scalar_t__ UINT_MAX ; 
 scalar_t__ ULONG_MAX ; 
 scalar_t__ boring ; 
 scalar_t__ chardata ; 
 char* format ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ intdata ; 
 scalar_t__ longdata ; 
 scalar_t__ nosign ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sepstring ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
putdata(double x, bool last)
{

	if (boring)
		printf("%s", format);
	else if (longdata && nosign) {
		if (x <= (double)ULONG_MAX && x >= (double)0)
			printf(format, (unsigned long)x);
		else
			return (1);
	} else if (longdata) {
		if (x <= (double)LONG_MAX && x >= (double)LONG_MIN)
			printf(format, (long)x);
		else
			return (1);
	} else if (chardata || (intdata && !nosign)) {
		if (x <= (double)INT_MAX && x >= (double)INT_MIN)
			printf(format, (int)x);
		else
			return (1);
	} else if (intdata) {
		if (x <= (double)UINT_MAX && x >= (double)0)
			printf(format, (unsigned int)x);
		else
			return (1);

	} else
		printf(format, x);
	if (!last)
		fputs(sepstring, stdout);

	return (0);
}