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
struct TYPE_3__ {int /*<<< orphan*/  declared_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_BLOB ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_odb_open_wstream (TYPE_1__**,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_odb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  odb ; 
 int /*<<< orphan*/  repo ; 
 TYPE_1__* stream ; 

void test_odb_streamwrite__initialize(void)
{
	repo = cl_git_sandbox_init("testrepo.git");
	cl_git_pass(git_repository_odb(&odb, repo));

	cl_git_pass(git_odb_open_wstream(&stream, odb, 14, GIT_OBJECT_BLOB));
	cl_assert_equal_sz(14, stream->declared_size);
}