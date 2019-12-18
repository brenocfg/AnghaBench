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
typedef  int /*<<< orphan*/  command ;
typedef  int /*<<< orphan*/  atf_tc_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int /*<<< orphan*/ ) ; 
 scalar_t__ EXIT_SUCCESS ; 
 int /*<<< orphan*/  atf_tc_fail (char*) ; 
 char* atf_tc_get_config_var (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  calculate_data (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int const) ; 
 scalar_t__ system (char*) ; 

__attribute__((used)) static void
one_check(const atf_tc_t *tc, const int test_length)
{
	FILE *out;
	char command[1024];

	ATF_REQUIRE((out = fopen("out", "w")) != NULL);
	calculate_data(out, test_length);
	fclose(out);

	/* XXX The following is a huge hack that was added to simplify the
	 * conversion of these tests from src/regress/ to src/tests/.  The
	 * tests in this file should be checking their own results, without
	 * having to resort to external data files. */
	snprintf(command, sizeof(command), "diff -u %s/d_bitstring_%d.out out",
	    atf_tc_get_config_var(tc, "srcdir"), test_length);
	if (system(command) != EXIT_SUCCESS)
		atf_tc_fail("Test failed; see output for details");
}