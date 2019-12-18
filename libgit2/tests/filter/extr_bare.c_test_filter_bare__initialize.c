#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BLOB_FILTER_ATTTRIBUTES_FROM_HEAD ; 
 int /*<<< orphan*/  GIT_BLOB_FILTER_NO_SYSTEM_ATTRIBUTES ; 
 int /*<<< orphan*/  cl_fixture_sandbox (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_1__ filter_opts ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ *,char*) ; 

void test_filter_bare__initialize(void)
{
	cl_fixture_sandbox("crlf.git");
	cl_git_pass(git_repository_open(&g_repo, "crlf.git"));

	filter_opts.flags |= GIT_BLOB_FILTER_NO_SYSTEM_ATTRIBUTES;
	filter_opts.flags |= GIT_BLOB_FILTER_ATTTRIBUTES_FROM_HEAD;
}