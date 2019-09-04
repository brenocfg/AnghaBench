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
struct TYPE_3__ {int /*<<< orphan*/  ptr; scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_fixture_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_cleanup () ; 
 TYPE_1__ expected_fixture ; 
 int /*<<< orphan*/  g_index ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ ) ; 

void test_index_crlf__cleanup(void)
{
	git_index_free(g_index);
	cl_git_sandbox_cleanup();

	if (expected_fixture.size) {
		cl_fixture_cleanup(expected_fixture.ptr);
		git_buf_dispose(&expected_fixture);
	}
}