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
 int GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  _packbuilder ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,char*) ; 
 int /*<<< orphan*/  git_oid_fmt (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_packbuilder_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_packbuilder_write (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seed_packbuilder () ; 

void test_pack_packbuilder__get_hash(void)
{
	char hex[GIT_OID_HEXSZ+1]; hex[GIT_OID_HEXSZ] = '\0';

	seed_packbuilder();

	git_packbuilder_write(_packbuilder, ".", 0, NULL, NULL);
	git_oid_fmt(hex, git_packbuilder_hash(_packbuilder));

	cl_assert_equal_s(hex, "7f5fa362c664d68ba7221259be1cbd187434b2f0");
}