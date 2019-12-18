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
struct descriptors {scalar_t__ testdir; void* root; void* usr; void* etc; int /*<<< orphan*/  binary; } ;
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 char* atf_tc_get_config_var (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  openat (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 void* opendir (char*) ; 
 void* opendirat (void*,char*) ; 

__attribute__((used)) static void
setup(struct descriptors *dp, const atf_tc_t *tc)
{

	dp->testdir = opendir(atf_tc_get_config_var(tc, "srcdir"));
	ATF_REQUIRE(dp->testdir >= 0);
	ATF_REQUIRE(
	    (dp->binary = openat(dp->testdir, "target", O_RDONLY)) >= 0);

	ATF_REQUIRE((dp->root = opendir("/")) >= 0);
	ATF_REQUIRE((dp->etc = opendirat(dp->root, "etc")) >= 0);
	ATF_REQUIRE((dp->usr = opendirat(dp->root, "usr")) >= 0);
}