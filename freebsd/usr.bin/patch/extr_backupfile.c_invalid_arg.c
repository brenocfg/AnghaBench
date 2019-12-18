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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
invalid_arg(const char *kind, const char *value, int problem)
{
	fprintf(stderr, "patch: ");
	if (problem == -1)
		fprintf(stderr, "invalid");
	else			/* Assume -2. */
		fprintf(stderr, "ambiguous");
	fprintf(stderr, " %s `%s'\n", kind, value);
}