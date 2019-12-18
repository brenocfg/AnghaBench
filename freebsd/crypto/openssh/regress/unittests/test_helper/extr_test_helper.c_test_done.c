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
 int /*<<< orphan*/ * active_test_name ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  quiet_mode ; 
 int /*<<< orphan*/  stdout ; 
 char* subtest_info ; 
 scalar_t__ verbose_mode ; 

void
test_done(void)
{
	*subtest_info = '\0';
	assert(active_test_name != NULL);
	free(active_test_name);
	active_test_name = NULL;
	if (verbose_mode)
		printf("OK\n");
	else if (!quiet_mode) {
		printf(".");
		fflush(stdout);
	}
}