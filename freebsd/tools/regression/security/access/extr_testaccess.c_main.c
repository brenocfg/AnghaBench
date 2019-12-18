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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  ROOT_UID ; 
 int /*<<< orphan*/  R_OK ; 
 int /*<<< orphan*/  TEST_GID_ONE ; 
 int /*<<< orphan*/  TEST_GID_TWO ; 
 int /*<<< orphan*/  TEST_UID_ONE ; 
 int /*<<< orphan*/  TEST_UID_TWO ; 
 int /*<<< orphan*/  WHEEL_GID ; 
 int access (char*,int /*<<< orphan*/ ) ; 
 int cleanup () ; 
 int eaccess (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ geteuid () ; 
 int /*<<< orphan*/  perror (char*) ; 
 int restoreprivilege () ; 
 int setgroups (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int setresgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int setresuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int setup () ; 
 int /*<<< orphan*/  stderr ; 

int
main(int argc, char *argv[])
{
	int error, errorseen;

	if (geteuid() != 0) {
		fprintf(stderr, "testaccess must run as root.\n");
		exit (EXIT_FAILURE);
	}

	error = setup();
	if (error) {
		cleanup();
		exit (EXIT_FAILURE);
	}

	/* Make sure saved uid is set appropriately. */
	error = setresuid(ROOT_UID, ROOT_UID, ROOT_UID);
	if (error) {
		perror("setresuid");
		cleanup();
	}

	/* Clear out additional groups. */
	error = setgroups(0, NULL);
	if (error) {
		perror("setgroups");
		cleanup();
	}

	/* Make sure saved gid is set appropriately. */
	error = setresgid(WHEEL_GID, WHEEL_GID, WHEEL_GID);
	if (error) {
		perror("setresgid");
		cleanup();
	}

	/*
	 * UID-only tests.
	 */

	/* Check that saved uid is not used */
	error = setresuid(TEST_UID_ONE, TEST_UID_ONE, ROOT_UID);
	if (error) {
		perror("setresuid.1");
		cleanup();
		exit (EXIT_FAILURE);
	}

	errorseen = 0;

	error = access("test1", R_OK);
	if (!error) {
		fprintf(stderr, "saved uid used instead of real uid\n");
		errorseen++;
	}

#ifdef EACCESS_AVAILABLE
	error = eaccess("test1", R_OK);
	if (!error) {
		fprintf(stderr, "saved uid used instead of effective uid\n");
		errorseen++;
	}
#endif

	error = restoreprivilege();
	if (error) {
		perror("restoreprivilege");
		cleanup();
		exit (EXIT_FAILURE);
	}

	error = setresuid(TEST_UID_ONE, TEST_UID_TWO, ROOT_UID);
	if (error) {
		perror("setresid.2");
		cleanup();
		exit (EXIT_FAILURE);
	}

	/* Check that the real uid is used, not the effective uid */
	error = access("test2", R_OK);
	if (error) {
		fprintf(stderr, "Effective uid was used instead of real uid in access().\n");
		errorseen++;
	}

#ifdef EACCESS_AVAILABLE
	/* Check that the effective uid is used, not the real uid */
	error = eaccess("test3", R_OK);
	if (error) {
		fprintf(stderr, "Real uid was used instead of effective uid in eaccess().\n");
		errorseen++;
	}
#endif

	/* Check that the real uid is used, not the effective uid */
	error = access("test3", R_OK);
	if (!error) {
		fprintf(stderr, "Effective uid was used instead of real uid in access().\n");
		errorseen++;
	}

#ifdef EACCESS_AVAILABLE
	/* Check that the effective uid is used, not the real uid */
	error = eaccess("test2", R_OK);
	if (!error) {
		fprintf(stderr, "Real uid was used instead of effective uid in eaccess().\n");
		errorseen++;
	}
#endif

	error = restoreprivilege();
	if (error) {
		perror("restoreprivilege");
		cleanup();
		exit (EXIT_FAILURE);
	}

	error = setresgid(TEST_GID_ONE, TEST_GID_TWO, WHEEL_GID);
	if (error) {
		perror("setresgid.1");
		cleanup();
		exit (EXIT_FAILURE);
	}

	/* Set non-root effective uid to avoid excess privilege. */
	error = setresuid(TEST_UID_ONE, TEST_UID_ONE, ROOT_UID);
	if (error) {
		perror("setresuid.3");
		cleanup();
		exit (EXIT_FAILURE);
	}

	/* Check that the saved gid is not used */
	error = access("test4", R_OK);
	if (!error) {
		fprintf(stderr, "saved gid used instead of real gid\n");
	}

#ifdef EACCESS_AVAILABLE
	error = eaccess("test4", R_OK);
	if (!error) {
		fprintf(stderr, "saved gid used instead of effective gid\n");
		errorseen++;
	}
#endif

	/* Check that the real gid is used, not the effective gid */
	error = access("test5", R_OK);
	if (error) {
		fprintf(stderr, "Effective gid was used instead of real gid in access().\n");
		errorseen++;
	}

#ifdef EACCESS_AVAILABLE
	/* Check that the effective gid is used, not the real gid */
	error = eaccess("test6", R_OK);
	if (error) {
		fprintf(stderr, "Real gid was used instead of effective gid in eaccess().\n");
		errorseen++;
	}
#endif

	/* Check that the real gid is used, not the effective gid */
	error = access("test6", R_OK);
	if (!error) {
		fprintf(stderr, "Effective gid was used instead of real gid in access().\n");
		errorseen++;
	}

#ifdef EACCESS_AVAILABLE
	/* Check that the effective gid is used, not the real gid */
	error = eaccess("test5", R_OK);
	if (!error) {
		fprintf(stderr, "Real gid was used instead of effective gid in eaccess().\n");
		errorseen++;
	}
#endif

	fprintf(stderr, "%d errors seen.\n", errorseen);

	/*
	 * All tests done, restore and clean up
	 */

	error = cleanup();
	if (error) {
		perror("cleanup");
		exit (EXIT_FAILURE);
	}

	exit (EXIT_SUCCESS);
}