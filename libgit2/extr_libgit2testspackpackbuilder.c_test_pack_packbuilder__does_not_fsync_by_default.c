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
 int /*<<< orphan*/  _packbuilder ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_packbuilder_write (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_fsync__cnt ; 
 int /*<<< orphan*/  seed_packbuilder () ; 

void test_pack_packbuilder__does_not_fsync_by_default(void)
{
	seed_packbuilder();
	git_packbuilder_write(_packbuilder, ".", 0666, NULL, NULL);
	cl_assert_equal_sz(0, p_fsync__cnt);
}