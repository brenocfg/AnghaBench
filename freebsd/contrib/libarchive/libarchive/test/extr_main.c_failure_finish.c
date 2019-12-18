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
 int /*<<< orphan*/  EXTRA_DUMP (void*) ; 
 int /*<<< orphan*/  EXTRA_ERRNO (void*) ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ dump_on_failure ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  logprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
failure_finish(void *extra)
{
	(void)extra; /* UNUSED (maybe) */
#ifdef EXTRA_DUMP
	if (extra != NULL) {
		logprintf("    errno: %d\n", EXTRA_ERRNO(extra));
		logprintf("   detail: %s\n", EXTRA_DUMP(extra));
	}
#endif

	if (dump_on_failure) {
		fprintf(stderr,
		    " *** forcing core dump so failure can be debugged ***\n");
		abort();
	}
}