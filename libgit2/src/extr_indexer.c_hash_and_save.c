#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct git_pack_entry {int /*<<< orphan*/  crc; int /*<<< orphan*/  oid; int /*<<< orphan*/  sha1; } ;
struct entry {int /*<<< orphan*/  crc; int /*<<< orphan*/  oid; int /*<<< orphan*/  sha1; } ;
struct TYPE_9__ {struct git_pack_entry* data; } ;
typedef  TYPE_2__ git_rawobj ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  scalar_t__ git_off_t ;
struct TYPE_10__ {TYPE_1__* pack; scalar_t__ off; } ;
typedef  TYPE_3__ git_indexer ;
struct TYPE_8__ {int /*<<< orphan*/  mwf; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (struct git_pack_entry*) ; 
 int /*<<< orphan*/  GIT_ERROR_INDEXER ; 
 int /*<<< orphan*/  Z_NULL ; 
 int /*<<< orphan*/  crc32 (long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ crc_object (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,size_t) ; 
 struct git_pack_entry* git__calloc (int,int) ; 
 int /*<<< orphan*/  git__free (struct git_pack_entry*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_odb__hashobj (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int save_entry (TYPE_3__*,struct git_pack_entry*,struct git_pack_entry*,scalar_t__) ; 

__attribute__((used)) static int hash_and_save(git_indexer *idx, git_rawobj *obj, git_off_t entry_start)
{
	git_oid oid;
	size_t entry_size;
	struct entry *entry;
	struct git_pack_entry *pentry = NULL;

	entry = git__calloc(1, sizeof(*entry));
	GIT_ERROR_CHECK_ALLOC(entry);

	if (git_odb__hashobj(&oid, obj) < 0) {
		git_error_set(GIT_ERROR_INDEXER, "failed to hash object");
		goto on_error;
	}

	pentry = git__calloc(1, sizeof(struct git_pack_entry));
	GIT_ERROR_CHECK_ALLOC(pentry);

	git_oid_cpy(&pentry->sha1, &oid);
	git_oid_cpy(&entry->oid, &oid);
	entry->crc = crc32(0L, Z_NULL, 0);

	entry_size = (size_t)(idx->off - entry_start);
	if (crc_object(&entry->crc, &idx->pack->mwf, entry_start, entry_size) < 0)
		goto on_error;

	return save_entry(idx, entry, pentry, entry_start);

on_error:
	git__free(pentry);
	git__free(entry);
	git__free(obj->data);
	return -1;
}