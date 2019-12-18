#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ fsync; int /*<<< orphan*/ * repo; } ;
typedef  TYPE_2__ refdb_fs_backend ;
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_19__ {scalar_t__ type; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ git_reference ;
struct TYPE_17__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_20__ {TYPE_1__ member_0; } ;
typedef  TYPE_4__ git_oid ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int GIT_EDIRECTORY ; 
 int GIT_EEXISTS ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_REFERENCE ; 
 int /*<<< orphan*/  GIT_HEAD_FILE ; 
 scalar_t__ GIT_REFERENCE_SYMBOLIC ; 
 int /*<<< orphan*/  GIT_REFLOG_FILE_MODE ; 
 int /*<<< orphan*/  GIT_RMDIR_SKIP_NONEMPTY ; 
 int O_APPEND ; 
 int O_CREAT ; 
 int O_FSYNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int git_futils_mkpath2file (int /*<<< orphan*/ ,int) ; 
 int git_futils_rmdir_r (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_futils_writebuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_cpy (TYPE_4__*,TYPE_4__ const*) ; 
 scalar_t__ git_path_isdir (int /*<<< orphan*/ ) ; 
 int git_reference_name_to_id (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_symbolic_target (TYPE_3__ const*) ; 
 TYPE_4__ const* git_reference_target (TYPE_3__ const*) ; 
 int retrieve_reflog_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int serialize_reflog_entry (int /*<<< orphan*/ *,TYPE_4__*,TYPE_4__*,int /*<<< orphan*/  const*,char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reflog_append(refdb_fs_backend *backend, const git_reference *ref, const git_oid *old, const git_oid *new, const git_signature *who, const char *message)
{
	int error, is_symbolic, open_flags;
	git_oid old_id = {{0}}, new_id = {{0}};
	git_buf buf = GIT_BUF_INIT, path = GIT_BUF_INIT;
	git_repository *repo = backend->repo;

	is_symbolic = ref->type == GIT_REFERENCE_SYMBOLIC;

	/* "normal" symbolic updates do not write */
	if (is_symbolic &&
	    strcmp(ref->name, GIT_HEAD_FILE) &&
	    !(old && new))
		return 0;

	/* From here on is_symbolic also means that it's HEAD */

	if (old) {
		git_oid_cpy(&old_id, old);
	} else {
		error = git_reference_name_to_id(&old_id, repo, ref->name);
		if (error < 0 && error != GIT_ENOTFOUND)
			return error;
	}

	if (new) {
		git_oid_cpy(&new_id, new);
	} else {
		if (!is_symbolic) {
			git_oid_cpy(&new_id, git_reference_target(ref));
		} else {
			error = git_reference_name_to_id(&new_id, repo, git_reference_symbolic_target(ref));
			if (error < 0 && error != GIT_ENOTFOUND)
				return error;
			/* detaching HEAD does not create an entry */
			if (error == GIT_ENOTFOUND)
				return 0;

			git_error_clear();
		}
	}

	if ((error = serialize_reflog_entry(&buf, &old_id, &new_id, who, message)) < 0)
		goto cleanup;

	if ((error = retrieve_reflog_path(&path, repo, ref->name)) < 0)
		goto cleanup;

	if (((error = git_futils_mkpath2file(git_buf_cstr(&path), 0777)) < 0) &&
	    (error != GIT_EEXISTS)) {
		goto cleanup;
	}

	/* If the new branch matches part of the namespace of a previously deleted branch,
	 * there maybe an obsolete/unused directory (or directory hierarchy) in the way.
	 */
	if (git_path_isdir(git_buf_cstr(&path))) {
		if ((error = git_futils_rmdir_r(git_buf_cstr(&path), NULL, GIT_RMDIR_SKIP_NONEMPTY)) < 0) {
			if (error == GIT_ENOTFOUND)
				error = 0;
		} else if (git_path_isdir(git_buf_cstr(&path))) {
			git_error_set(GIT_ERROR_REFERENCE, "cannot create reflog at '%s', there are reflogs beneath that folder",
				ref->name);
			error = GIT_EDIRECTORY;
		}

		if (error != 0)
			goto cleanup;
	}

	open_flags = O_WRONLY | O_CREAT | O_APPEND;

	if (backend->fsync)
		open_flags |= O_FSYNC;

	error = git_futils_writebuffer(&buf, git_buf_cstr(&path), open_flags, GIT_REFLOG_FILE_MODE);

cleanup:
	git_buf_dispose(&buf);
	git_buf_dispose(&path);

	return error;
}