#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* header; int header_len; scalar_t__ new_lines; scalar_t__ old_lines; } ;
typedef  TYPE_1__ git_diff_hunk ;
typedef  int /*<<< orphan*/  git_diff_delta ;
struct TYPE_5__ {int /*<<< orphan*/  hunk_new_lines; int /*<<< orphan*/  hunk_old_lines; int /*<<< orphan*/  hunks; } ;
typedef  TYPE_2__ diff_expects ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cl_assert (int) ; 

int diff_hunk_cb(
	const git_diff_delta *delta,
	const git_diff_hunk *hunk,
	void *payload)
{
	diff_expects *e = payload;
	const char *scan = hunk->header, *scan_end = scan + hunk->header_len;

	GIT_UNUSED(delta);

	/* confirm no NUL bytes in header text */
	while (scan < scan_end)
		cl_assert('\0' != *scan++);

	e->hunks++;
	e->hunk_old_lines += hunk->old_lines;
	e->hunk_new_lines += hunk->new_lines;
	return 0;
}