#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct addrinfo_test_data {int dummy; } ;
struct addrinfo {int dummy; } ;
struct TYPE_3__ {int ai_family; int /*<<< orphan*/  ai_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AI_CANONNAME ; 
 int /*<<< orphan*/  ATF_CHECK (int) ; 
 int /*<<< orphan*/  ATF_REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,char*) ; 
 int /*<<< orphan*/  DO_2PASS_TEST (int /*<<< orphan*/ ,struct addrinfo_test_data*,struct addrinfo_test_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ENOENT ; 
 int R_OK ; 
#define  TEST_BUILD_SNAPSHOT 129 
 int /*<<< orphan*/  TEST_DATA_DESTROY (int /*<<< orphan*/ ,struct addrinfo_test_data*) ; 
 int /*<<< orphan*/  TEST_DATA_INIT (int /*<<< orphan*/ ,struct addrinfo_test_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  TEST_GETADDRINFO 128 
 int TEST_SNAPSHOT_FILE_READ (int /*<<< orphan*/ ,char const*,struct addrinfo_test_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_SNAPSHOT_FILE_WRITE (int /*<<< orphan*/ ,char const*,struct addrinfo_test_data*,int /*<<< orphan*/ ) ; 
 int W_OK ; 
 scalar_t__ access (char const*,int) ; 
 int /*<<< orphan*/  addrinfo ; 
 int /*<<< orphan*/  addrinfo_read_hostlist_func ; 
 int /*<<< orphan*/  addrinfo_read_snapshot_func ; 
 int /*<<< orphan*/  clone_addrinfo ; 
 int /*<<< orphan*/  compare_addrinfo ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_addrinfo ; 
 TYPE_1__ hints ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int method ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  sdump_addrinfo ; 
 char* strdup (char const*) ; 
 char* strerror (scalar_t__) ; 

__attribute__((used)) static void
run_tests(char *hostlist_file, const char *snapshot_file, int ai_family)
{
	struct addrinfo_test_data td, td_snap;
	char *snapshot_file_copy;
	int rv;

	if (snapshot_file == NULL)
		snapshot_file_copy = NULL;
	else {
		snapshot_file_copy = strdup(snapshot_file);
		ATF_REQUIRE(snapshot_file_copy != NULL);
	}

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = ai_family;
	hints.ai_flags = AI_CANONNAME;

	if (snapshot_file != NULL)
		method = TEST_BUILD_SNAPSHOT;

	TEST_DATA_INIT(addrinfo, &td, clone_addrinfo, free_addrinfo);
	TEST_DATA_INIT(addrinfo, &td_snap, clone_addrinfo, free_addrinfo);

	ATF_REQUIRE_MSG(access(hostlist_file, R_OK) == 0,
		"can't access the hostlist file %s\n", hostlist_file);

	printf("building host lists from %s\n", hostlist_file);

	rv = TEST_SNAPSHOT_FILE_READ(addrinfo, hostlist_file, &td,
		addrinfo_read_hostlist_func);
	if (rv != 0)
		goto fin;

	if (snapshot_file != NULL) {
		if (access(snapshot_file, W_OK | R_OK) != 0) {
			if (errno == ENOENT)
				method = TEST_BUILD_SNAPSHOT;
			else {
				printf("can't access the snapshot "
				    "file %s\n", snapshot_file);

				rv = -1;
				goto fin;
			}
		} else {
			rv = TEST_SNAPSHOT_FILE_READ(addrinfo, snapshot_file,
				&td_snap, addrinfo_read_snapshot_func);
			if (rv != 0) {
				printf("error reading snapshot file: %s\n",
				    strerror(errno));
				goto fin;
			}
		}
	}

	switch (method) {
	case TEST_GETADDRINFO:
		if (snapshot_file != NULL)
			ATF_CHECK(DO_2PASS_TEST(addrinfo, &td, &td_snap,
				compare_addrinfo, NULL) == 0);
		break;
	case TEST_BUILD_SNAPSHOT:
		if (snapshot_file != NULL) {
			ATF_CHECK(TEST_SNAPSHOT_FILE_WRITE(addrinfo,
			    snapshot_file, &td, sdump_addrinfo) == 0);
		}
		break;
	default:
		break;
	}

fin:
	TEST_DATA_DESTROY(addrinfo, &td_snap);
	TEST_DATA_DESTROY(addrinfo, &td);

	free(snapshot_file_copy);
}