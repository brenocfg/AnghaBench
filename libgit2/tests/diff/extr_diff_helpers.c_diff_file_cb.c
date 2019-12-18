#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  path; } ;
struct TYPE_7__ {size_t status; int flags; TYPE_1__ old_file; } ;
typedef  TYPE_2__ git_diff_delta ;
struct TYPE_8__ {size_t files; int* file_status; int /*<<< orphan*/  files_binary; int /*<<< orphan*/ * statuses; int /*<<< orphan*/ * names; scalar_t__ debug; } ;
typedef  TYPE_3__ diff_expects ;

/* Variables and functions */
 size_t GIT_DELTA_CONFLICTED ; 
 int GIT_DIFF_FLAG_BINARY ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf_delta (int /*<<< orphan*/ ,TYPE_2__ const*,float) ; 
 int /*<<< orphan*/  stderr ; 

int diff_file_cb(
	const git_diff_delta *delta,
	float progress,
	void *payload)
{
	diff_expects *e = payload;

	if (e->debug)
		fprintf_delta(stderr, delta, progress);

	if (e->names)
		cl_assert_equal_s(e->names[e->files], delta->old_file.path);
	if (e->statuses)
		cl_assert_equal_i(e->statuses[e->files], (int)delta->status);

	e->files++;

	if ((delta->flags & GIT_DIFF_FLAG_BINARY) != 0)
		e->files_binary++;

	cl_assert(delta->status <= GIT_DELTA_CONFLICTED);

	e->file_status[delta->status] += 1;

	return 0;
}