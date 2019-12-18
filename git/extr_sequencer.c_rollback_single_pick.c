#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct repository {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_cherry_pick_head (struct repository*) ; 
 int /*<<< orphan*/  git_path_revert_head (struct repository*) ; 
 scalar_t__ is_null_oid (struct object_id*) ; 
 scalar_t__ read_ref_full (char*,int /*<<< orphan*/ ,struct object_id*,int /*<<< orphan*/ *) ; 
 int reset_merge (struct object_id*) ; 

__attribute__((used)) static int rollback_single_pick(struct repository *r)
{
	struct object_id head_oid;

	if (!file_exists(git_path_cherry_pick_head(r)) &&
	    !file_exists(git_path_revert_head(r)))
		return error(_("no cherry-pick or revert in progress"));
	if (read_ref_full("HEAD", 0, &head_oid, NULL))
		return error(_("cannot resolve HEAD"));
	if (is_null_oid(&head_oid))
		return error(_("cannot abort from a branch yet to be born"));
	return reset_merge(&head_oid);
}