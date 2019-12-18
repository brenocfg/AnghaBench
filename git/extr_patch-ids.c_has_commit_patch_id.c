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
struct patch_ids {int /*<<< orphan*/  patches; } ;
struct patch_id {int dummy; } ;
struct commit {int dummy; } ;
typedef  int /*<<< orphan*/  patch ;

/* Variables and functions */
 int /*<<< orphan*/  ent ; 
 struct patch_id* hashmap_get_entry (int /*<<< orphan*/ *,struct patch_id*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ init_patch_id_entry (struct patch_id*,struct commit*,struct patch_ids*) ; 
 int /*<<< orphan*/  memset (struct patch_id*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  patch_id_defined (struct commit*) ; 

struct patch_id *has_commit_patch_id(struct commit *commit,
				     struct patch_ids *ids)
{
	struct patch_id patch;

	if (!patch_id_defined(commit))
		return NULL;

	memset(&patch, 0, sizeof(patch));
	if (init_patch_id_entry(&patch, commit, ids))
		return NULL;

	return hashmap_get_entry(&ids->patches, &patch, ent, NULL);
}