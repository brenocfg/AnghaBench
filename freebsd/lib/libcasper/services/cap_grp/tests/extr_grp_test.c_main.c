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
 int GETGRENT ; 
 int GETGRENT_R ; 
 int GETGRGID ; 
 int GETGRGID_R ; 
 int GETGRNAM ; 
 int GETGRNAM_R ; 
 int SETGRENT ; 
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
 int /*<<< orphan*/  test_groups (int /*<<< orphan*/ *) ; 

int
main(void)
{
	cap_channel_t *capcas, *capgrp;

	printf("1..199\n");
	fflush(stdout);

	capcas = cap_init();
	CHECKX(capcas != NULL);

	capgrp = cap_service_open(capcas, "system.grp");
	CHECKX(capgrp != NULL);

	cap_close(capcas);

	/* No limits. */

	CHECK(runtest_cmds(capgrp) == (SETGRENT | GETGRENT | GETGRENT_R |
	    GETGRNAM | GETGRNAM_R | GETGRGID | GETGRGID_R));

	test_cmds(capgrp);

	test_fields(capgrp);

	test_groups(capgrp);

	cap_close(capgrp);

	exit(0);
}