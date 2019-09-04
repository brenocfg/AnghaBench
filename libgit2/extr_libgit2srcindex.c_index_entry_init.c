#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_13__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_index_entry ;
struct TYPE_14__ {int /*<<< orphan*/  distrust_filemode; } ;
typedef  TYPE_2__ git_index ;
struct TYPE_15__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_3__ git_buf ;

/* Variables and functions */
 TYPE_3__ GIT_BUF_INIT ; 
 int GIT_EBAREREPO ; 
 int /*<<< orphan*/ * INDEX_OWNER (TYPE_2__*) ; 
 int create_index_error (int,char*) ; 
 int git_blob__create_from_paths (int /*<<< orphan*/ *,struct stat*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_3__*) ; 
 scalar_t__ git_buf_joinpath (TYPE_3__*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_index_entry__init_from_stat (TYPE_1__*,struct stat*,int) ; 
 int git_path_lstat (int /*<<< orphan*/ ,struct stat*) ; 
 scalar_t__ git_repository__ensure_not_bare (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ *) ; 
 scalar_t__ index_entry_create (TYPE_1__**,int /*<<< orphan*/ *,char const*,struct stat*,int) ; 
 int /*<<< orphan*/  index_entry_free (TYPE_1__*) ; 

__attribute__((used)) static int index_entry_init(
	git_index_entry **entry_out,
	git_index *index,
	const char *rel_path)
{
	int error = 0;
	git_index_entry *entry = NULL;
	git_buf path = GIT_BUF_INIT;
	struct stat st;
	git_oid oid;
	git_repository *repo;

	if (INDEX_OWNER(index) == NULL)
		return create_index_error(-1,
			"could not initialize index entry. "
			"Index is not backed up by an existing repository.");

	/*
	 * FIXME: this is duplicated with the work in
	 * git_blob__create_from_paths. It should accept an optional stat
	 * structure so we can pass in the one we have to do here.
	 */
	repo = INDEX_OWNER(index);
	if (git_repository__ensure_not_bare(repo, "create blob from file") < 0)
		return GIT_EBAREREPO;

	if (git_buf_joinpath(&path, git_repository_workdir(repo), rel_path) < 0)
		return -1;

	error = git_path_lstat(path.ptr, &st);
	git_buf_dispose(&path);

	if (error < 0)
		return error;

	if (index_entry_create(&entry, INDEX_OWNER(index), rel_path, &st, true) < 0)
		return -1;

	/* write the blob to disk and get the oid and stat info */
	error = git_blob__create_from_paths(
		&oid, &st, INDEX_OWNER(index), NULL, rel_path, 0, true);

	if (error < 0) {
		index_entry_free(entry);
		return error;
	}

	entry->id = oid;
	git_index_entry__init_from_stat(entry, &st, !index->distrust_filemode);

	*entry_out = (git_index_entry *)entry;
	return 0;
}