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
typedef  int /*<<< orphan*/  cwd ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  abspath ; 
 int /*<<< orphan*/  asprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  dirfd ; 
 int /*<<< orphan*/ * getcwd (char*,int) ; 
 scalar_t__ mkdir (char*,int) ; 
 scalar_t__ mkdirat (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  open (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ symlinkat (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  touchat (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
prepare_dotdot_tests(void)
{
	char cwd[MAXPATHLEN];

	ATF_REQUIRE(getcwd(cwd, sizeof(cwd)) != NULL);
	asprintf(&abspath, "%s/testdir/d1/f1", cwd);

	ATF_REQUIRE(mkdir("testdir", 0777) == 0);
	ATF_REQUIRE((dirfd = open("testdir", O_RDONLY)) >= 0);

	ATF_REQUIRE(mkdirat(dirfd, "d1", 0777) == 0);
	ATF_REQUIRE(mkdirat(dirfd, "d1/d2", 0777) == 0);
	ATF_REQUIRE(mkdirat(dirfd, "d1/d2/d3", 0777) == 0);
	touchat(dirfd, "d1/f1");
	touchat(dirfd, "d1/d2/f2");
	touchat(dirfd, "d1/d2/d3/f3");
	ATF_REQUIRE(symlinkat("d1/d2/d3", dirfd, "l3") == 0);
	ATF_REQUIRE(symlinkat("../testdir/d1", dirfd, "lup") == 0);
	ATF_REQUIRE(symlinkat("../..", dirfd, "d1/d2/d3/ld1") == 0);
	ATF_REQUIRE(symlinkat("../../f1", dirfd, "d1/d2/d3/lf1") == 0);
}