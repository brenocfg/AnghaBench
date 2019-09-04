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
struct TYPE_3__ {char** member_0; int member_1; } ;
typedef  TYPE_1__ git_strarray ;

/* Variables and functions */
 scalar_t__ _remote ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_upload (scalar_t__,TYPE_1__*,int /*<<< orphan*/ *) ; 

void test_online_push__bad_refspecs(void)
{
	/* All classes of refspecs that should be rejected by
	 * git_push_add_refspec() should go in this test.
	 */
	char *specs = {
		"b6:b6",
	};
	git_strarray arr = {
		&specs,
		1,
	};

	if (_remote) {
		cl_git_fail(git_remote_upload(_remote, &arr, NULL));
	}
}