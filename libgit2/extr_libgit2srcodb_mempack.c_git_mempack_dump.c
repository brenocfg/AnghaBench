#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_2__ {size_t size; struct memobject** ptr; } ;
struct memory_packer_db {TYPE_1__ commits; } ;
struct memobject {int /*<<< orphan*/  oid; } ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_packbuilder ;
typedef  int /*<<< orphan*/  git_odb_backend ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  git_packbuilder_free (int /*<<< orphan*/ *) ; 
 int git_packbuilder_insert_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ git_packbuilder_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int git_packbuilder_write_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int git_mempack_dump(git_buf *pack, git_repository *repo, git_odb_backend *_backend)
{
	struct memory_packer_db *db = (struct memory_packer_db *)_backend;
	git_packbuilder *packbuilder;
	uint32_t i;
	int err = -1;

	if (git_packbuilder_new(&packbuilder, repo) < 0)
		return -1;

	for (i = 0; i < db->commits.size; ++i) {
		struct memobject *commit = db->commits.ptr[i];

		err = git_packbuilder_insert_commit(packbuilder, &commit->oid);
		if (err < 0)
			goto cleanup;
	}

	err = git_packbuilder_write_buf(pack, packbuilder);

cleanup:
	git_packbuilder_free(packbuilder);
	return err;
}