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
struct TYPE_3__ {scalar_t__ datatype; int /*<<< orphan*/  matches; } ;
typedef  TYPE_1__ git_pathspec_match_list ;
typedef  int /*<<< orphan*/  git_diff_delta ;

/* Variables and functions */
 scalar_t__ PATHSPEC_DATATYPE_DIFF ; 
 scalar_t__ git_array_get (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  git_array_valid_index (int /*<<< orphan*/ ,size_t) ; 

const git_diff_delta *git_pathspec_match_list_diff_entry(
	const git_pathspec_match_list *m, size_t pos)
{
	if (!m || m->datatype != PATHSPEC_DATATYPE_DIFF ||
		!git_array_valid_index(m->matches, pos))
		return NULL;

	return *((const git_diff_delta **)git_array_get(m->matches, pos));
}