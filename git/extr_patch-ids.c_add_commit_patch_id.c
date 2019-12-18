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
struct patch_id {int /*<<< orphan*/  ent; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct patch_id*) ; 
 int /*<<< orphan*/  hashmap_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ init_patch_id_entry (struct patch_id*,struct commit*,struct patch_ids*) ; 
 int /*<<< orphan*/  patch_id_defined (struct commit*) ; 
 struct patch_id* xcalloc (int,int) ; 

struct patch_id *add_commit_patch_id(struct commit *commit,
				     struct patch_ids *ids)
{
	struct patch_id *key;

	if (!patch_id_defined(commit))
		return NULL;

	key = xcalloc(1, sizeof(*key));
	if (init_patch_id_entry(key, commit, ids)) {
		free(key);
		return NULL;
	}

	hashmap_add(&ids->patches, &key->ent);
	return key;
}