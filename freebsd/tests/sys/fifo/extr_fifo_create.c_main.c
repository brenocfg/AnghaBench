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
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atexit_temp_dir ; 
 scalar_t__ chdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  fifo_create_test (int) ; 
 int /*<<< orphan*/  fifo_permission_test (int) ; 
 scalar_t__ geteuid () ; 
 int /*<<< orphan*/ * mkdtemp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  temp_dir ; 

int
main(void)
{
	int i;

	if (geteuid() != 0)
		errx(-1, "must be run as root");

	strcpy(temp_dir, "fifo_create.XXXXXXXXXXX");
	if (mkdtemp(temp_dir) == NULL)
		err(-1, "mkdtemp");
	atexit(atexit_temp_dir);

	if (chdir(temp_dir) < 0)
		err(-1, "chdir");

	/*
	 * Run each test twice, once with mknod(2) and a second time with
	 * mkfifo(2).  Historically, BSD has not allowed mknod(2) to be used
	 * to create fifos, but the Single UNIX Specification requires it.
	 */
	for (i = 0; i < 2; i++) {
		fifo_create_test(i);
		fifo_permission_test(i);
	}

	return (0);
}