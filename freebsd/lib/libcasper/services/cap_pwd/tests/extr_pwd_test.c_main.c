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
typedef  int /*<<< orphan*/  cap_channel_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int) ; 
 int /*<<< orphan*/  CHECKX (int /*<<< orphan*/ ) ; 
 int GETPWENT ; 
 int GETPWENT_R ; 
 int GETPWNAM ; 
 int GETPWNAM_R ; 
 int GETPWUID ; 
 int GETPWUID_R ; 
 int /*<<< orphan*/  cap_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cap_init () ; 
 int /*<<< orphan*/ * cap_service_open (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int runtest_cmds (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  test_cmds (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_fields (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_users (int /*<<< orphan*/ *) ; 

int
main(void)
{
	cap_channel_t *capcas, *cappwd;

	printf("1..188\n");
	fflush(stdout);

	capcas = cap_init();
	CHECKX(capcas != NULL);

	cappwd = cap_service_open(capcas, "system.pwd");
	CHECKX(cappwd != NULL);

	cap_close(capcas);

	/* No limits. */

	CHECK(runtest_cmds(cappwd) == (GETPWENT | GETPWENT_R | GETPWNAM |
	    GETPWNAM_R | GETPWUID | GETPWUID_R));

	test_cmds(cappwd);

	test_fields(cappwd);

	test_users(cappwd);

	cap_close(cappwd);

	exit(0);
}