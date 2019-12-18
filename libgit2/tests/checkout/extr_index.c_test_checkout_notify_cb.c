#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct notify_data {int /*<<< orphan*/  sha; int /*<<< orphan*/  file; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_diff_file ;
typedef  int /*<<< orphan*/  git_checkout_notify_t ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CHECKOUT_NOTIFY_CONFLICT ; 
 int /*<<< orphan*/  GIT_UNUSED (TYPE_1__ const*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_oid_streq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_checkout_notify_cb(
	git_checkout_notify_t why,
	const char *path,
	const git_diff_file *baseline,
	const git_diff_file *target,
	const git_diff_file *workdir,
	void *payload)
{
	struct notify_data *expectations = (struct notify_data *)payload;

	GIT_UNUSED(workdir);

	cl_assert_equal_i(GIT_CHECKOUT_NOTIFY_CONFLICT, why);
	cl_assert_equal_s(expectations->file, path);
	cl_assert_equal_i(0, git_oid_streq(&baseline->id, expectations->sha));
	cl_assert_equal_i(0, git_oid_streq(&target->id, expectations->sha));

	return 0;
}