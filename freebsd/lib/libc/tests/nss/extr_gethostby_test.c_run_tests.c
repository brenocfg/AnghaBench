#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hostent_test_data {int dummy; } ;
typedef  TYPE_1__* res_state ;
typedef  enum test_methods { ____Placeholder_test_methods } test_methods ;
struct TYPE_4__ {int options; } ;

/* Variables and functions */
#define  AF_INET 135 
#define  AF_INET6 134 
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  ATF_REQUIRE_FEATURE (char*) ; 
 int DO_1PASS_TEST (int /*<<< orphan*/ ,struct hostent_test_data*,int /*<<< orphan*/ ,void*) ; 
 int DO_2PASS_TEST (int /*<<< orphan*/ ,struct hostent_test_data*,struct hostent_test_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ENOENT ; 
 int RES_INIT ; 
 int RES_USE_INET6 ; 
 int R_OK ; 
#define  TEST_BUILD_ADDR_SNAPSHOT 133 
#define  TEST_BUILD_SNAPSHOT 132 
 int /*<<< orphan*/  TEST_DATA_DESTROY (int /*<<< orphan*/ ,struct hostent_test_data*) ; 
 int /*<<< orphan*/  TEST_DATA_INIT (int /*<<< orphan*/ ,struct hostent_test_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  TEST_GETHOSTBYADDR 131 
#define  TEST_GETHOSTBYADDR_GETNAMEINFO 130 
#define  TEST_GETHOSTBYNAME2 129 
#define  TEST_GETHOSTBYNAME2_GETADDRINFO 128 
 int TEST_SNAPSHOT_FILE_READ (int /*<<< orphan*/ ,char const*,struct hostent_test_data*,int /*<<< orphan*/ ) ; 
 int TEST_SNAPSHOT_FILE_WRITE (int /*<<< orphan*/ ,char const*,struct hostent_test_data*,int /*<<< orphan*/ ) ; 
 int W_OK ; 
 TYPE_1__* __res_state () ; 
 scalar_t__ access (char const*,int) ; 
 int /*<<< orphan*/  atf_tc_fail (char*,int) ; 
 int /*<<< orphan*/  clone_hostent ; 
 int /*<<< orphan*/  compare_hostent ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_hostent ; 
 int /*<<< orphan*/  hostent ; 
 int /*<<< orphan*/  hostent_read_hostlist_func ; 
 int /*<<< orphan*/  hostent_read_snapshot_func ; 
 int /*<<< orphan*/  hostent_test_getaddrinfo_eq ; 
 int /*<<< orphan*/  hostent_test_gethostbyaddr ; 
 int /*<<< orphan*/  hostent_test_getnameinfo_eq ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int res_ninit (TYPE_1__*) ; 
 int /*<<< orphan*/  sdump_hostent ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  use_ipnode_functions ; 

__attribute__((used)) static int
run_tests(const char *hostlist_file, const char *snapshot_file, int _af_type,
    enum test_methods method, bool use_ipv6_mapping)
{
	char *snapshot_file_copy;
	struct hostent_test_data td, td_addr, td_snap;
	res_state statp;
	int rv = -2;

	if (snapshot_file == NULL)
		snapshot_file_copy = NULL;
	else {
		snapshot_file_copy = strdup(snapshot_file);
		ATF_REQUIRE(snapshot_file_copy != NULL);
	}
	snapshot_file = snapshot_file_copy;

	switch (_af_type) {
	case AF_INET:
		ATF_REQUIRE_FEATURE("inet");
		ATF_REQUIRE(!use_ipv6_mapping);
		break;
	case AF_INET6:
		ATF_REQUIRE_FEATURE("inet6");
		break;
	default:
		atf_tc_fail("unhandled address family: %d", _af_type);
		break;
	}

	if (!use_ipnode_functions) {
		statp = __res_state();
		if (statp == NULL || ((statp->options & RES_INIT) == 0 &&
		    res_ninit(statp) == -1)) {
			printf("error: can't init res_state\n");
			rv = -1;
			goto fin2;
		}

		if (use_ipv6_mapping)
			statp->options |= RES_USE_INET6;
		else
			statp->options &= ~RES_USE_INET6;
	}

	TEST_DATA_INIT(hostent, &td, clone_hostent, free_hostent);
	TEST_DATA_INIT(hostent, &td_addr, clone_hostent, free_hostent);
	TEST_DATA_INIT(hostent, &td_snap, clone_hostent, free_hostent);

	if (access(hostlist_file, R_OK) != 0) {
		printf("can't access the hostlist file %s\n", hostlist_file);
		rv = -1;
		goto fin;
	}

#ifdef DEBUG
	printf("building host lists from %s\n", hostlist_file);
#endif

	rv = TEST_SNAPSHOT_FILE_READ(hostent, hostlist_file, &td,
		hostent_read_hostlist_func);
	if (rv != 0) {
		printf("failed to read the host list file: %s\n",
		    hostlist_file);
		goto fin;
	}

	if (snapshot_file != NULL) {
		if (access(snapshot_file, W_OK | R_OK) != 0) {
			if (errno == ENOENT) {
				if (method != TEST_GETHOSTBYADDR)
					method = TEST_BUILD_SNAPSHOT;
				else
					method = TEST_BUILD_ADDR_SNAPSHOT;
			} else {
				printf("can't access the snapshot file %s\n",
				    snapshot_file);
				rv = -1;
				goto fin;
			}
		} else {
			rv = TEST_SNAPSHOT_FILE_READ(hostent, snapshot_file,
				&td_snap, hostent_read_snapshot_func);
			if (rv != 0) {
				printf("error reading snapshot file\n");
				goto fin;
			}
		}
	}

	switch (method) {
	case TEST_GETHOSTBYNAME2:
		if (snapshot_file != NULL)
			rv = DO_2PASS_TEST(hostent, &td, &td_snap,
			    compare_hostent, NULL);
		break;
	case TEST_GETHOSTBYADDR:
		rv = DO_1PASS_TEST(hostent, &td,
			hostent_test_gethostbyaddr, (void *)&td_addr);
		if (rv != 0)
			goto fin;

		if (snapshot_file != NULL)
			rv = DO_2PASS_TEST(hostent, &td_addr, &td_snap,
			    compare_hostent, NULL);
		break;
	case TEST_GETHOSTBYNAME2_GETADDRINFO:
		rv = DO_1PASS_TEST(hostent, &td,
			hostent_test_getaddrinfo_eq, NULL);
		break;
	case TEST_GETHOSTBYADDR_GETNAMEINFO:
		rv = DO_1PASS_TEST(hostent, &td,
			hostent_test_getnameinfo_eq, NULL);
		break;
	case TEST_BUILD_SNAPSHOT:
		if (snapshot_file != NULL) {
			rv = TEST_SNAPSHOT_FILE_WRITE(hostent, snapshot_file,
			    &td, sdump_hostent);
		}
		break;
	case TEST_BUILD_ADDR_SNAPSHOT:
		if (snapshot_file != NULL) {
			rv = DO_1PASS_TEST(hostent, &td,
			    hostent_test_gethostbyaddr, (void *)&td_addr);
			if (rv != 0)
				goto fin;
			rv = TEST_SNAPSHOT_FILE_WRITE(hostent, snapshot_file,
			    &td_addr, sdump_hostent);
		}
		break;
	default:
		rv = 0;
		break;
	}

fin:
	TEST_DATA_DESTROY(hostent, &td_snap);
	TEST_DATA_DESTROY(hostent, &td_addr);
	TEST_DATA_DESTROY(hostent, &td);

fin2:
	free(snapshot_file_copy);

	return (rv);
}