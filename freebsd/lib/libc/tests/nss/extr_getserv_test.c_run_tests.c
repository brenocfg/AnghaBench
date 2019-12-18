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
struct servent_test_data {int dummy; } ;
typedef  enum test_methods { ____Placeholder_test_methods } test_methods ;

/* Variables and functions */
 int DO_1PASS_TEST (int /*<<< orphan*/ ,struct servent_test_data*,int /*<<< orphan*/ ,void*) ; 
 int DO_2PASS_TEST (int /*<<< orphan*/ ,struct servent_test_data*,struct servent_test_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ENOENT ; 
 int R_OK ; 
#define  TEST_BUILD_SNAPSHOT 132 
 int /*<<< orphan*/  TEST_DATA_DESTROY (int /*<<< orphan*/ ,struct servent_test_data*) ; 
 int /*<<< orphan*/  TEST_DATA_INIT (int /*<<< orphan*/ ,struct servent_test_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  TEST_GETSERVBYNAME 131 
#define  TEST_GETSERVBYPORT 130 
#define  TEST_GETSERVENT 129 
#define  TEST_GETSERVENT_2PASS 128 
 int /*<<< orphan*/  TEST_SNAPSHOT_FILE_READ (int /*<<< orphan*/ ,char const*,struct servent_test_data*,int /*<<< orphan*/ ) ; 
 int TEST_SNAPSHOT_FILE_WRITE (int /*<<< orphan*/ ,char const*,struct servent_test_data*,int /*<<< orphan*/ ) ; 
 int W_OK ; 
 scalar_t__ access (char const*,int) ; 
 int /*<<< orphan*/  clone_servent ; 
 int /*<<< orphan*/  compare_servent ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free_servent ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  sdump_servent ; 
 int /*<<< orphan*/  servent ; 
 int servent_fill_test_data (struct servent_test_data*) ; 
 int /*<<< orphan*/  servent_read_snapshot_func ; 
 int /*<<< orphan*/  servent_test_getservbyname ; 
 int /*<<< orphan*/  servent_test_getservbyport ; 
 int /*<<< orphan*/  servent_test_getservent ; 

__attribute__((used)) static int
run_tests(const char *snapshot_file, enum test_methods method)
{
	struct servent_test_data td, td_snap, td_2pass;
	int rv;

	TEST_DATA_INIT(servent, &td, clone_servent, free_servent);
	TEST_DATA_INIT(servent, &td_snap, clone_servent, free_servent);
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

			TEST_SNAPSHOT_FILE_READ(servent, snapshot_file,
				&td_snap, servent_read_snapshot_func);
		}
	}

	rv = servent_fill_test_data(&td);
	if (rv == -1)
		return (-1);
	switch (method) {
	case TEST_GETSERVBYNAME:
		if (snapshot_file == NULL)
			rv = DO_1PASS_TEST(servent, &td,
				servent_test_getservbyname, (void *)&td);
		else
			rv = DO_1PASS_TEST(servent, &td_snap,
				servent_test_getservbyname, (void *)&td_snap);
		break;
	case TEST_GETSERVBYPORT:
		if (snapshot_file == NULL)
			rv = DO_1PASS_TEST(servent, &td,
				servent_test_getservbyport, (void *)&td);
		else
			rv = DO_1PASS_TEST(servent, &td_snap,
				servent_test_getservbyport, (void *)&td_snap);
		break;
	case TEST_GETSERVENT:
		if (snapshot_file == NULL)
			rv = DO_1PASS_TEST(servent, &td, servent_test_getservent,
				(void *)&td);
		else
			rv = DO_2PASS_TEST(servent, &td, &td_snap,
				compare_servent, NULL);
		break;
	case TEST_GETSERVENT_2PASS:
			TEST_DATA_INIT(servent, &td_2pass, clone_servent, free_servent);
			rv = servent_fill_test_data(&td_2pass);
			if (rv != -1)
				rv = DO_2PASS_TEST(servent, &td, &td_2pass,
					compare_servent, NULL);
			TEST_DATA_DESTROY(servent, &td_2pass);
		break;
	case TEST_BUILD_SNAPSHOT:
		if (snapshot_file != NULL)
		    rv = TEST_SNAPSHOT_FILE_WRITE(servent, snapshot_file, &td,
			sdump_servent);
		break;
	default:
		rv = 0;
		break;
	}

fin:
	TEST_DATA_DESTROY(servent, &td_snap);
	TEST_DATA_DESTROY(servent, &td);

	return (rv);
}