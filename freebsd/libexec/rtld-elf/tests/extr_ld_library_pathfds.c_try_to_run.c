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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  atf_tc_fail (char*) ; 
 scalar_t__ atf_utils_fork () ; 
 int /*<<< orphan*/  atf_utils_wait (scalar_t__,int,char const*,char const*) ; 
 int /*<<< orphan*/  fexecve (int,char* const*,char* const*) ; 

__attribute__((used)) static void
try_to_run(int binary, int exit_status, char * const *env,
        const char *expected_out, const char *expected_err)
{
	pid_t child = atf_utils_fork();

	if (child == 0) {
		char * const args[] = { "target", NULL };

		fexecve(binary, args, env);
		atf_tc_fail("fexecve() failed");
	}

	atf_utils_wait(child, exit_status, expected_out, expected_err);
}