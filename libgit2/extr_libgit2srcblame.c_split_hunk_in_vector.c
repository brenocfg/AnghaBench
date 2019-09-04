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
typedef  int /*<<< orphan*/  git_vector ;
struct TYPE_6__ {size_t lines_in_hunk; int /*<<< orphan*/  orig_commit_id; int /*<<< orphan*/  final_commit_id; int /*<<< orphan*/  orig_path; scalar_t__ orig_start_line_number; scalar_t__ final_start_line_number; } ;
typedef  TYPE_1__ git_blame_hunk ;

/* Variables and functions */
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_insert_sorted (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* new_hunk (scalar_t__,size_t,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static git_blame_hunk *split_hunk_in_vector(
		git_vector *vec,
		git_blame_hunk *hunk,
		size_t rel_line,
		bool return_new)
{
	size_t new_line_count;
	git_blame_hunk *nh;

	/* Don't split if already at a boundary */
	if (rel_line <= 0 ||
	    rel_line >= hunk->lines_in_hunk)
	{
		return hunk;
	}

	new_line_count = hunk->lines_in_hunk - rel_line;
	nh = new_hunk(hunk->final_start_line_number + rel_line, new_line_count,
			hunk->orig_start_line_number + rel_line, hunk->orig_path);

	if (!nh)
		return NULL;

	git_oid_cpy(&nh->final_commit_id, &hunk->final_commit_id);
	git_oid_cpy(&nh->orig_commit_id, &hunk->orig_commit_id);

	/* Adjust hunk that was split */
	hunk->lines_in_hunk -= new_line_count;
	git_vector_insert_sorted(vec, nh, NULL);
	{
		git_blame_hunk *ret = return_new ? nh : hunk;
		return ret;
	}
}