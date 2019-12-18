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
struct TYPE_3__ {scalar_t__ new_lines; scalar_t__ old_lines; } ;
typedef  TYPE_1__ git_diff_hunk ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (void*) ; 

__attribute__((used)) static int skip_change(
	const git_diff_hunk *hunk,
	void *payload)
{
	GIT_UNUSED(payload);

	return (hunk->new_lines == hunk->old_lines) ? 1 : 0;
}