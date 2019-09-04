#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  matched_pathspec; int /*<<< orphan*/ * path; } ;
typedef  TYPE_2__ notify_expected ;
struct TYPE_5__ {int /*<<< orphan*/  path; } ;
struct TYPE_7__ {TYPE_1__ new_file; } ;
typedef  TYPE_3__ git_diff_delta ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int assert_called_notifications(
	const git_diff *diff_so_far,
	const git_diff_delta *delta_to_add,
	const char *matched_pathspec,
	void *payload)
{
	bool found = false;
	notify_expected *exp = (notify_expected*)payload;
	notify_expected *e;

	GIT_UNUSED(diff_so_far);

	for (e = exp; e->path != NULL; e++) {
		if (strcmp(e->path, delta_to_add->new_file.path))
			continue;

		cl_assert_equal_s(e->matched_pathspec, matched_pathspec);

		found = true;
		break;
	}

	cl_assert(found);
	return 0;
}