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
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 int /*<<< orphan*/  AFILE ; 
 int /*<<< orphan*/  ATF_REQUIRE_ERRNO (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EROFS ; 
 int /*<<< orphan*/  FSTEST_ENTER () ; 
 int /*<<< orphan*/  FSTEST_EXIT () ; 
 int O_CREAT ; 
 int O_RDONLY ; 
 int rump_sys_open (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
create(const atf_tc_t *tc, const char *mp)
{

	FSTEST_ENTER();
	ATF_REQUIRE_ERRNO(EROFS, rump_sys_open(AFILE, O_CREAT|O_RDONLY) == -1);
	FSTEST_EXIT();
}