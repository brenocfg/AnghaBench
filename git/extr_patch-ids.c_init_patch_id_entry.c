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
struct patch_ids {int /*<<< orphan*/  diffopts; } ;
struct patch_id {int /*<<< orphan*/  ent; struct commit* commit; } ;
struct object_id {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 scalar_t__ commit_patch_id (struct commit*,int /*<<< orphan*/ *,struct object_id*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_entry_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oidhash (struct object_id*) ; 

__attribute__((used)) static int init_patch_id_entry(struct patch_id *patch,
			       struct commit *commit,
			       struct patch_ids *ids)
{
	struct object_id header_only_patch_id;

	patch->commit = commit;
	if (commit_patch_id(commit, &ids->diffopts, &header_only_patch_id, 1, 0))
		return -1;

	hashmap_entry_init(&patch->ent, oidhash(&header_only_patch_id));
	return 0;
}