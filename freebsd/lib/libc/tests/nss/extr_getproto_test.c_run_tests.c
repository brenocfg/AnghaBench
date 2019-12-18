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
struct protoent_test_data {int dummy; } ;
typedef  enum test_methods { ____Placeholder_test_methods } test_methods ;

/* Variables and functions */
 int DO_1PASS_TEST (int /*<<< orphan*/ ,struct protoent_test_data*,int /*<<< orphan*/ ,void*) ; 
 int DO_2PASS_TEST (int /*<<< orphan*/ ,struct protoent_test_data*,struct protoent_test_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ENOENT ; 
 int R_OK ; 
#define  TEST_BUILD_SNAPSHOT 132 
 int /*<<< orphan*/  TEST_DATA_DESTROY (int /*<<< orphan*/ ,struct protoent_test_data*) ; 
 int /*<<< orphan*/  TEST_DATA_INIT (int /*<<< orphan*/ ,struct protoent_test_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  TEST_GETPROTOBYNAME 131 
#define  TEST_GETPROTOBYNUMBER 130 
#define  TEST_GETPROTOENT 129 
#define  TEST_GETPROTOENT_2PASS 128 
 int /*<<< orphan*/  TEST_SNAPSHOT_FILE_READ (int /*<<< orphan*/ ,char const*,struct protoent_test_data*,int /*<<< orphan*/ ) ; 
 int TEST_SNAPSHOT_FILE_WRITE (int /*<<< orphan*/ ,char const*,struct protoent_test_data*,int /*<<< orphan*/ ) ; 
 int W_OK ; 
 scalar_t__ access (char const*,int) ; 
 int /*<<< orphan*/  clone_protoent ; 
 int /*<<< orphan*/  compare_protoent ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free_protoent ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  protoent ; 
 int protoent_fill_test_data (struct protoent_test_data*) ; 
 int /*<<< orphan*/  protoent_read_snapshot_func ; 
 int /*<<< orphan*/  protoent_test_getprotobyname ; 
 int /*<<< orphan*/  protoent_test_getprotobynumber ; 
 int /*<<< orphan*/  protoent_test_getprotoent ; 
 int /*<<< orphan*/  sdump_protoent ; 

__attribute__((used)) static int
run_tests(const char *snapshot_file, enum test_methods method)
{
	struct protoent_test_data td, td_snap, td_2pass;
	int rv;

	TEST_DATA_INIT(protoent, &td, clone_protoent, free_protoent);
	TEST_DATA_INIT(protoent, &td_snap, clone_protoent, free_protoent);
	if (snapshot_file != NULL) {
		if (access(snapshot_file, W_OK | R_OK) != 0) {
			if (errno == ENOENT)
				method = TEST_BUILD_SNAPSHOT;
			else {
				printf("can't access the file %s\n",
				    snapshot_file);

				rv = -1;
				goto fin;
			}
		} else {
			if (method == TEST_BUILD_SNAPSHOT) {
				rv = 0;
				goto fin;
			}

			TEST_SNAPSHOT_FILE_READ(protoent, snapshot_file,
				&td_snap, protoent_read_snapshot_func);
		}
	}

	rv = protoent_fill_test_data(&td);
	if (rv == -1)
		return (-1);
	switch (method) {
	case TEST_GETPROTOBYNAME:
		if (snapshot_file == NULL)
			rv = DO_1PASS_TEST(protoent, &td,
				protoent_test_getprotobyname, (void *)&td);
		else
			rv = DO_1PASS_TEST(protoent, &td_snap,
				protoent_test_getprotobyname, (void *)&td_snap);
		break;
	case TEST_GETPROTOBYNUMBER:
		if (snapshot_file == NULL)
			rv = DO_1PASS_TEST(protoent, &td,
				protoent_test_getprotobynumber, (void *)&td);
		else
			rv = DO_1PASS_TEST(protoent, &td_snap,
				protoent_test_getprotobynumber, (void *)&td_snap);
		break;
	case TEST_GETPROTOENT:
		if (snapshot_file == NULL)
			rv = DO_1PASS_TEST(protoent, &td,
				protoent_test_getprotoent, (void *)&td);
		else
			rv = DO_2PASS_TEST(protoent, &td, &td_snap,
				compare_protoent, NULL);
		break;
	case TEST_GETPROTOENT_2PASS:
		TEST_DATA_INIT(protoent, &td_2pass, clone_protoent,
		    free_protoent);
		rv = protoent_fill_test_data(&td_2pass);
		if (rv != -1)
			rv = DO_2PASS_TEST(protoent, &td, &td_2pass,
				compare_protoent, NULL);
		TEST_DATA_DESTROY(protoent, &td_2pass);
		break;
	case TEST_BUILD_SNAPSHOT:
		if (snapshot_file != NULL)
			rv = TEST_SNAPSHOT_FILE_WRITE(protoent, snapshot_file,
			    &td, sdump_protoent);
		break;
	default:
		rv = 0;
		break;
	}

fin:
	TEST_DATA_DESTROY(protoent, &td_snap);
	TEST_DATA_DESTROY(protoent, &td);

	return (rv);
}