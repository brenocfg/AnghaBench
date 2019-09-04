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
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  ensure_no_refname_starts_with_a_forward_slash (int /*<<< orphan*/ ) ; 

void test_refs_listall__from_repository_opened_through_gitdir_path(void)
{
	ensure_no_refname_starts_with_a_forward_slash(cl_fixture("testrepo.git"));
}