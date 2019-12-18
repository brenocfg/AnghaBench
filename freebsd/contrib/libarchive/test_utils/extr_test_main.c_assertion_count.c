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
 int /*<<< orphan*/  assertions ; 
 int /*<<< orphan*/ * msg ; 
 int /*<<< orphan*/ * nextmsg ; 

__attribute__((used)) static void
assertion_count(const char *file, int line)
{
	(void)file; /* UNUSED */
	(void)line; /* UNUSED */
	++assertions;
	/* Proper handling of "failure()" message. */
	msg = nextmsg;
	nextmsg = NULL;
	/* Uncomment to print file:line after every assertion.
	 * Verbose, but occasionally useful in tracking down crashes. */
	/* printf("Checked %s:%d\n", file, line); */
}