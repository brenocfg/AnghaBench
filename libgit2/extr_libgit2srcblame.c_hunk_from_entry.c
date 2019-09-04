#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int boundary; int /*<<< orphan*/  final_signature; int /*<<< orphan*/  orig_signature; int /*<<< orphan*/  orig_commit_id; int /*<<< orphan*/  final_commit_id; } ;
typedef  TYPE_2__ git_blame_hunk ;
struct TYPE_11__ {scalar_t__ is_boundary; TYPE_1__* suspect; scalar_t__ s_lno; int /*<<< orphan*/  num_lines; scalar_t__ lno; } ;
typedef  TYPE_3__ git_blame__entry ;
struct TYPE_12__ {int /*<<< orphan*/  mailmap; } ;
typedef  TYPE_4__ git_blame ;
struct TYPE_9__ {int /*<<< orphan*/  commit; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  git_commit_author_with_mailmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_commit_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_signature_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* new_hunk (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static git_blame_hunk* hunk_from_entry(git_blame__entry *e, git_blame *blame)
{
	git_blame_hunk *h = new_hunk(
			e->lno+1, e->num_lines, e->s_lno+1, e->suspect->path);

	if (!h)
		return NULL;

	git_oid_cpy(&h->final_commit_id, git_commit_id(e->suspect->commit));
	git_oid_cpy(&h->orig_commit_id, git_commit_id(e->suspect->commit));
	git_commit_author_with_mailmap(
		&h->final_signature, e->suspect->commit, blame->mailmap);
	git_signature_dup(&h->orig_signature, h->final_signature);
	h->boundary = e->is_boundary ? 1 : 0;
	return h;
}