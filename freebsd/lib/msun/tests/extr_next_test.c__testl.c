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
 int /*<<< orphan*/  ALL_STD_EXCEPT ; 
 int /*<<< orphan*/  abort () ; 
 int fetestexcept (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpequal (long double,long double) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char const*,int,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
_testl(const char *exp, int line, long double actual, long double expected,
    int except)
{
	int actual_except;

	actual_except = fetestexcept(ALL_STD_EXCEPT);
	if (!fpequal(actual, expected)) {
		fprintf(stderr, "%d: %s returned %La, expecting %La\n",
		    line, exp, actual, expected);
		abort();
	}
	if (actual_except != except) {
		fprintf(stderr, "%d: %s raised 0x%x, expecting 0x%x\n",
		    line, exp, actual_except, except);
		abort();
	}
}