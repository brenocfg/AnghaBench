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
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char const*,...) ; 
 int /*<<< orphan*/  stderr ; 

void
__assert(const char *func, const char *file, int line, const char *failedexpr)
{
	if (func == NULL)
		(void)fprintf(stderr,
		     "Assertion failed: (%s), file %s, line %d.\n", failedexpr,
		     file, line);
	else
		(void)fprintf(stderr,
		     "Assertion failed: (%s), function %s, file %s, line %d.\n",
		     failedexpr, func, file, line);
	abort();
	/* NOTREACHED */
}