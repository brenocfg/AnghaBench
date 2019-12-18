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
struct proc_handle {int dummy; } ;
struct atf_tc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATF_REQUIRE_EQ_MSG (int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asprintf (char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_tc_get_config_var (struct atf_tc const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int proc_create (char*,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct proc_handle**) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  target_prog_file ; 

__attribute__((used)) static struct proc_handle *
start_prog(const struct atf_tc *tc, bool sig)
{
	char *argv[3];
	struct proc_handle *phdl;
	int error;

	asprintf(&argv[0], "%s/%s", atf_tc_get_config_var(tc, "srcdir"),
	    target_prog_file);
	ATF_REQUIRE(argv[0] != NULL);

	if (sig) {
		argv[1] = strdup("-s");
		argv[2] = NULL;
	} else {
		argv[1] = NULL;
	}

	error = proc_create(argv[0], argv, NULL, NULL, NULL, &phdl);
	ATF_REQUIRE_EQ_MSG(error, 0, "failed to run '%s'", target_prog_file);
	ATF_REQUIRE(phdl != NULL);

	free(argv[0]);
	free(argv[1]);

	return (phdl);
}