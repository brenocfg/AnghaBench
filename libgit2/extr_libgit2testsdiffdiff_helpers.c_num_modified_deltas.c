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
struct TYPE_3__ {scalar_t__ status; } ;
typedef  TYPE_1__ git_diff_delta ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 scalar_t__ GIT_DELTA_UNMODIFIED ; 
 TYPE_1__* git_diff_get_delta (int /*<<< orphan*/ *,size_t) ; 
 size_t git_diff_num_deltas (int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t num_modified_deltas(git_diff *diff)
{
	const git_diff_delta *delta;
	size_t i, cnt = 0;

	for (i = 0; i < git_diff_num_deltas(diff); i++) {
		delta = git_diff_get_delta(diff, i);

		if (delta->status != GIT_DELTA_UNMODIFIED)
			cnt++;
	}

	return cnt;
}