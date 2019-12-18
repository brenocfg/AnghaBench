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
struct usershell_test_data {int dummy; } ;
struct usershell {int /*<<< orphan*/ * path; } ;
typedef  enum test_methods { ____Placeholder_test_methods } test_methods ;

/* Variables and functions */
 int DO_2PASS_TEST (int /*<<< orphan*/ ,struct usershell_test_data*,struct usershell_test_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ENOENT ; 
 int R_OK ; 
#define  TEST_BUILD_SNAPSHOT 129 
 int /*<<< orphan*/  TEST_DATA_APPEND (int /*<<< orphan*/ ,struct usershell_test_data*,struct usershell*) ; 
 int /*<<< orphan*/  TEST_DATA_DESTROY (int /*<<< orphan*/ ,struct usershell_test_data*) ; 
 int /*<<< orphan*/  TEST_DATA_INIT (int /*<<< orphan*/ ,struct usershell_test_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  TEST_GETUSERSHELL 128 
 int TEST_SNAPSHOT_FILE_READ (int /*<<< orphan*/ ,char const*,struct usershell_test_data*,int /*<<< orphan*/ ) ; 
 int TEST_SNAPSHOT_FILE_WRITE (int /*<<< orphan*/ ,char const*,struct usershell_test_data*,int /*<<< orphan*/ ) ; 
 int W_OK ; 
 scalar_t__ access (char const*,int) ; 
 int /*<<< orphan*/  clone_usershell ; 
 int /*<<< orphan*/  compare_usershell ; 
 int /*<<< orphan*/  dump_usershell (struct usershell*) ; 
 int /*<<< orphan*/  endusershell () ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free_usershell ; 
 int /*<<< orphan*/ * getusershell () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sdump_usershell ; 
 int /*<<< orphan*/  setusershell () ; 
 int /*<<< orphan*/  usershell ; 
 int /*<<< orphan*/  usershell_read_snapshot_func ; 

__attribute__((used)) static int
run_tests(const char *snapshot_file, enum test_methods method)
{
	struct usershell_test_data td, td_snap;
	struct usershell ushell;
	int rv;

	rv = 0;

	TEST_DATA_INIT(usershell, &td, clone_usershell, free_usershell);
	TEST_DATA_INIT(usershell, &td_snap, clone_usershell, free_usershell);

	setusershell();
	while ((ushell.path = getusershell()) != NULL) {
		printf("usershell found:\n");
		dump_usershell(&ushell);
		TEST_DATA_APPEND(usershell, &td, &ushell);
	}
	endusershell();

	if (snapshot_file != NULL) {
		if (access(snapshot_file, W_OK | R_OK) != 0) {
			if (errno == ENOENT)
				method = TEST_BUILD_SNAPSHOT;
			else {
				printf("can't access the snapshot file %s\n",
				    snapshot_file);

				rv = -1;
				goto fin;
			}
		} else {
			rv = TEST_SNAPSHOT_FILE_READ(usershell, snapshot_file,
				&td_snap, usershell_read_snapshot_func);
			if (rv != 0) {
				printf("error reading snapshot file\n");
				goto fin;
			}
		}
	}

	switch (method) {
	case TEST_GETUSERSHELL:
		rv = DO_2PASS_TEST(usershell, &td, &td_snap,
			compare_usershell, NULL);
		break;
	case TEST_BUILD_SNAPSHOT:
		if (snapshot_file != NULL) {
			rv = TEST_SNAPSHOT_FILE_WRITE(usershell, snapshot_file,
			    &td, sdump_usershell);
		}
		break;
	default:
		rv = 0;
		break;
	}

fin:
	TEST_DATA_DESTROY(usershell, &td_snap);
	TEST_DATA_DESTROY(usershell, &td);

	return (rv);
}