#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct git_pack_entry {int /*<<< orphan*/  crc; int /*<<< orphan*/  oid; int /*<<< orphan*/  sha1; scalar_t__ offset; scalar_t__ offset_long; } ;
struct entry {int /*<<< orphan*/  crc; int /*<<< orphan*/  oid; int /*<<< orphan*/  sha1; scalar_t__ offset; scalar_t__ offset_long; } ;
struct TYPE_13__ {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ git_rawobj ;
struct TYPE_14__ {int* id; } ;
typedef  TYPE_4__ git_oid ;
typedef  scalar_t__ git_off_t ;
struct TYPE_11__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
struct TYPE_15__ {scalar_t__ entry_start; scalar_t__ off; int /*<<< orphan*/ * fanout; int /*<<< orphan*/  objects; TYPE_2__* pack; int /*<<< orphan*/  entry_type; TYPE_1__ entry_data; scalar_t__ do_verify; int /*<<< orphan*/  hash_ctx; } ;
typedef  TYPE_5__ git_indexer ;
struct TYPE_12__ {int /*<<< orphan*/  mwf; int /*<<< orphan*/  idx_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (struct git_pack_entry*) ; 
 int /*<<< orphan*/  GIT_ERROR_INDEXER ; 
 scalar_t__ UINT31_MAX ; 
 scalar_t__ UINT32_MAX ; 
 int check_object_connectivity (TYPE_5__*,TYPE_3__*) ; 
 scalar_t__ crc_object (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 struct git_pack_entry* git__calloc (int,int) ; 
 int /*<<< orphan*/  git__free (struct git_pack_entry*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_set_oom () ; 
 int /*<<< orphan*/  git_hash_final (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  git_oid_tostr_s (int /*<<< orphan*/ *) ; 
 scalar_t__ git_oidmap_exists (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int git_oidmap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct git_pack_entry*) ; 
 scalar_t__ git_vector_insert (int /*<<< orphan*/ *,struct git_pack_entry*) ; 

__attribute__((used)) static int store_object(git_indexer *idx)
{
	int i, error;
	git_oid oid;
	struct entry *entry;
	git_off_t entry_size;
	struct git_pack_entry *pentry;
	git_off_t entry_start = idx->entry_start;

	entry = git__calloc(1, sizeof(*entry));
	GIT_ERROR_CHECK_ALLOC(entry);

	pentry = git__calloc(1, sizeof(struct git_pack_entry));
	GIT_ERROR_CHECK_ALLOC(pentry);

	git_hash_final(&oid, &idx->hash_ctx);
	entry_size = idx->off - entry_start;
	if (entry_start > UINT31_MAX) {
		entry->offset = UINT32_MAX;
		entry->offset_long = entry_start;
	} else {
		entry->offset = (uint32_t)entry_start;
	}

	if (idx->do_verify) {
		git_rawobj rawobj = {
		    idx->entry_data.ptr,
		    idx->entry_data.size,
		    idx->entry_type
		};

		if ((error = check_object_connectivity(idx, &rawobj)) < 0)
			goto on_error;
	}

	git_oid_cpy(&pentry->sha1, &oid);
	pentry->offset = entry_start;

	if (git_oidmap_exists(idx->pack->idx_cache, &pentry->sha1)) {
		git_error_set(GIT_ERROR_INDEXER, "duplicate object %s found in pack", git_oid_tostr_s(&pentry->sha1));
		git__free(pentry);
		goto on_error;
	}

	if ((error = git_oidmap_set(idx->pack->idx_cache, &pentry->sha1, pentry)) < 0) {
		git__free(pentry);
		git_error_set_oom();
		goto on_error;
	}

	git_oid_cpy(&entry->oid, &oid);

	if (crc_object(&entry->crc, &idx->pack->mwf, entry_start, entry_size) < 0)
		goto on_error;

	/* Add the object to the list */
	if (git_vector_insert(&idx->objects, entry) < 0)
		goto on_error;

	for (i = oid.id[0]; i < 256; ++i) {
		idx->fanout[i]++;
	}

	return 0;

on_error:
	git__free(entry);

	return -1;
}