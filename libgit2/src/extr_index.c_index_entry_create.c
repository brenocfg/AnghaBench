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
typedef  int /*<<< orphan*/  uint16_t ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  path; } ;
struct entry_internal {size_t pathlen; int /*<<< orphan*/  path; TYPE_1__ entry; } ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_index_entry ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (struct entry_internal*) ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_ADD (size_t*,size_t,int) ; 
 int /*<<< orphan*/  GIT_ERROR_INDEX ; 
 unsigned int GIT_PATH_REJECT_INDEX_DEFAULTS ; 
 unsigned int GIT_PATH_REJECT_WORKDIR_DEFAULTS ; 
 struct entry_internal* git__calloc (int,size_t) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  git_path_isvalid (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int index_entry_create(
	git_index_entry **out,
	git_repository *repo,
	const char *path,
	struct stat *st,
	bool from_workdir)
{
	size_t pathlen = strlen(path), alloclen;
	struct entry_internal *entry;
	unsigned int path_valid_flags = GIT_PATH_REJECT_INDEX_DEFAULTS;
	uint16_t mode = 0;

	/* always reject placing `.git` in the index and directory traversal.
	 * when requested, disallow platform-specific filenames and upgrade to
	 * the platform-specific `.git` tests (eg, `git~1`, etc).
	 */
	if (from_workdir)
		path_valid_flags |= GIT_PATH_REJECT_WORKDIR_DEFAULTS;
	if (st)
		mode = st->st_mode;

	if (!git_path_isvalid(repo, path, mode, path_valid_flags)) {
		git_error_set(GIT_ERROR_INDEX, "invalid path: '%s'", path);
		return -1;
	}

	GIT_ERROR_CHECK_ALLOC_ADD(&alloclen, sizeof(struct entry_internal), pathlen);
	GIT_ERROR_CHECK_ALLOC_ADD(&alloclen, alloclen, 1);
	entry = git__calloc(1, alloclen);
	GIT_ERROR_CHECK_ALLOC(entry);

	entry->pathlen = pathlen;
	memcpy(entry->path, path, pathlen);
	entry->entry.path = entry->path;

	*out = (git_index_entry *)entry;
	return 0;
}