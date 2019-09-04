#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  new_name; int /*<<< orphan*/  old_name; } ;
typedef  TYPE_1__ rename_cb_data ;
typedef  int /*<<< orphan*/  normalized ;
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_refname_t ;
struct TYPE_11__ {int /*<<< orphan*/  name; TYPE_8__* db; } ;
typedef  TYPE_2__ git_reference ;
struct TYPE_12__ {int /*<<< orphan*/  repo; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int git_branch_is_head (TYPE_2__*) ; 
 int git_refdb_rename (TYPE_2__**,TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/ * git_reference_owner (TYPE_2__*) ; 
 int git_repository_foreach_head (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int git_repository_set_head (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int reference_normalize_for_repo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  update_wt_heads ; 

__attribute__((used)) static int reference__rename(git_reference **out, git_reference *ref, const char *new_name, int force,
				 const git_signature *signature, const char *message)
{
	git_repository *repo;
	git_refname_t normalized;
	bool should_head_be_updated = false;
	int error = 0;

	assert(ref && new_name && signature);

	repo = git_reference_owner(ref);

	if ((error = reference_normalize_for_repo(
		normalized, repo, new_name, true)) < 0)
		return error;

	/* Check if we have to update HEAD. */
	if ((error = git_branch_is_head(ref)) < 0)
		return error;

	should_head_be_updated = (error > 0);

	if ((error = git_refdb_rename(out, ref->db, ref->name, normalized, force, signature, message)) < 0)
		return error;

	/* Update HEAD if it was pointing to the reference being renamed */
	if (should_head_be_updated) {
		error = git_repository_set_head(ref->db->repo, normalized);
	} else {
		rename_cb_data payload;
		payload.old_name = ref->name;
		memcpy(&payload.new_name, &normalized, sizeof(normalized));

		error = git_repository_foreach_head(repo, update_wt_heads, 0, &payload);
	}

	return error;
}