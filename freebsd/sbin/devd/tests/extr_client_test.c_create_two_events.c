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
typedef  int /*<<< orphan*/  mdname ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATF_REQUIRE_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nitems (char*) ; 
 int /*<<< orphan*/  pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void
create_two_events(void)
{
	FILE *create_stdout;
	FILE *destroy_stdout;
	char mdname[80];
	char destroy_cmd[95];
	char *error;

	create_stdout = popen("mdconfig -a -s 64 -t null", "r");
	ATF_REQUIRE(create_stdout != NULL);
	error = fgets(mdname, sizeof(mdname), create_stdout);
	ATF_REQUIRE(error != NULL);
	/* We only expect one line of output */
	ATF_REQUIRE_EQ(0, pclose(create_stdout));

	snprintf(destroy_cmd, nitems(destroy_cmd), "mdconfig -d -u %s", mdname);
	destroy_stdout = popen(destroy_cmd, "r");
	ATF_REQUIRE(destroy_stdout != NULL);
	/* We expect no output */
	ATF_REQUIRE_EQ(0, pclose(destroy_stdout));
}