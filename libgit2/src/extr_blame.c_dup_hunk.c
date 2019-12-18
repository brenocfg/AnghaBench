#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  orig_signature; int /*<<< orphan*/  final_signature; int /*<<< orphan*/  boundary; int /*<<< orphan*/  final_commit_id; int /*<<< orphan*/  orig_commit_id; int /*<<< orphan*/  orig_path; int /*<<< orphan*/  orig_start_line_number; int /*<<< orphan*/  lines_in_hunk; int /*<<< orphan*/  final_start_line_number; } ;
typedef  TYPE_1__ git_blame_hunk ;

/* Variables and functions */
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* new_hunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static git_blame_hunk* dup_hunk(git_blame_hunk *hunk)
{
	git_blame_hunk *newhunk = new_hunk(
			hunk->final_start_line_number,
			hunk->lines_in_hunk,
			hunk->orig_start_line_number,
			hunk->orig_path);

	if (!newhunk)
		return NULL;

	git_oid_cpy(&newhunk->orig_commit_id, &hunk->orig_commit_id);
	git_oid_cpy(&newhunk->final_commit_id, &hunk->final_commit_id);
	newhunk->boundary = hunk->boundary;
	git_signature_dup(&newhunk->final_signature, hunk->final_signature);
	git_signature_dup(&newhunk->orig_signature, hunk->orig_signature);
	return newhunk;
}