#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  clar_sandbox_path () ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  p_unlink (int /*<<< orphan*/ ) ; 
 int try_create_file_with_nsec_timestamp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool should_expect_nsecs(void)
{
	git_buf nsec_path = GIT_BUF_INIT;
	bool expect;

	git_buf_joinpath(&nsec_path, clar_sandbox_path(), "nsec_test");

	expect = try_create_file_with_nsec_timestamp(nsec_path.ptr);

	p_unlink(nsec_path.ptr);

	git_buf_dispose(&nsec_path);

	return expect;
}