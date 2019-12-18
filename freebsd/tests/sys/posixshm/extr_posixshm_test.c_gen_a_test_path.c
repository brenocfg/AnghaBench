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
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_PATH_LEN ; 
 int /*<<< orphan*/  errno ; 
 char* getenv (char*) ; 
 int mkstemp (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*,int) ; 
 int test_path_idx ; 
 scalar_t__ unlink (char*) ; 

__attribute__((used)) static void
gen_a_test_path(char *path)
{
	snprintf(path, TEST_PATH_LEN, "%s/tmp.XXXXXX%d",
	    getenv("TMPDIR") == NULL ? "/tmp" : getenv("TMPDIR"),
	    test_path_idx);

	test_path_idx++;

	ATF_REQUIRE_MSG(mkstemp(path) != -1,
	    "mkstemp failed; errno=%d", errno);
	ATF_REQUIRE_MSG(unlink(path) == 0,
	    "unlink failed; errno=%d", errno);
}