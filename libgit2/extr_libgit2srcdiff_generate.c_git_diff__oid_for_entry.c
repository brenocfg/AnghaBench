#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  git_submodule ;
typedef  int /*<<< orphan*/  const git_oid ;
struct TYPE_18__ {int /*<<< orphan*/  const id; scalar_t__ mode; scalar_t__ file_size; int /*<<< orphan*/  path; } ;
typedef  TYPE_3__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_filter_list ;
struct TYPE_16__ {int /*<<< orphan*/  oid_calculations; int /*<<< orphan*/  stat_calls; } ;
struct TYPE_17__ {int /*<<< orphan*/  repo; TYPE_1__ perf; } ;
struct TYPE_19__ {int diffcaps; int index_updated; TYPE_2__ base; } ;
typedef  TYPE_4__ git_diff_generated ;
struct TYPE_20__ {scalar_t__ type; } ;
typedef  TYPE_5__ git_diff ;
struct TYPE_21__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_6__ git_buf ;

/* Variables and functions */
 TYPE_6__ GIT_BUF_INIT ; 
 int GIT_DIFFCAPS_TRUST_MODE_BITS ; 
 scalar_t__ GIT_DIFF_TYPE_GENERATED ; 
 int /*<<< orphan*/  GIT_ERROR_NOMEMORY ; 
 int /*<<< orphan*/  GIT_FILTER_ALLOW_UNSAFE ; 
 int /*<<< orphan*/  GIT_FILTER_TO_ODB ; 
 int /*<<< orphan*/  GIT_OBJECT_BLOB ; 
 scalar_t__ S_ISGITLINK (scalar_t__) ; 
 scalar_t__ S_ISLNK (scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  git__is_sizet (scalar_t__) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_6__*) ; 
 scalar_t__ git_buf_joinpath (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_filter_list_free (int /*<<< orphan*/ *) ; 
 int git_filter_list_load (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_futils_open_ro (int /*<<< orphan*/ ) ; 
 int git_index_add (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  git_index_entry__init_from_stat (TYPE_3__*,struct stat*,int) ; 
 int git_odb__hashfd_filtered (int /*<<< orphan*/  const*,int,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int git_odb__hashlink (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ git_oid_equal (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int git_path_set_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int git_repository_index__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_submodule_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* git_submodule_wd_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  p_close (int) ; 
 scalar_t__ p_stat (int /*<<< orphan*/ ,struct stat*) ; 

int git_diff__oid_for_entry(
	git_oid *out,
	git_diff *d,
	const git_index_entry *src,
	uint16_t mode,
	const git_oid *update_match)
{
	git_diff_generated *diff;
	git_buf full_path = GIT_BUF_INIT;
	git_index_entry entry = *src;
	git_filter_list *fl = NULL;
	int error = 0;

	assert(d->type == GIT_DIFF_TYPE_GENERATED);
	diff = (git_diff_generated *)d;

	memset(out, 0, sizeof(*out));

	if (git_buf_joinpath(&full_path,
		git_repository_workdir(diff->base.repo), entry.path) < 0)
		return -1;

	if (!mode) {
		struct stat st;

		diff->base.perf.stat_calls++;

		if (p_stat(full_path.ptr, &st) < 0) {
			error = git_path_set_error(errno, entry.path, "stat");
			git_buf_dispose(&full_path);
			return error;
		}

		git_index_entry__init_from_stat(&entry,
			&st, (diff->diffcaps & GIT_DIFFCAPS_TRUST_MODE_BITS) != 0);
	}

	/* calculate OID for file if possible */
	if (S_ISGITLINK(mode)) {
		git_submodule *sm;

		if (!git_submodule_lookup(&sm, diff->base.repo, entry.path)) {
			const git_oid *sm_oid = git_submodule_wd_id(sm);
			if (sm_oid)
				git_oid_cpy(out, sm_oid);
			git_submodule_free(sm);
		} else {
			/* if submodule lookup failed probably just in an intermediate
			 * state where some init hasn't happened, so ignore the error
			 */
			git_error_clear();
		}
	} else if (S_ISLNK(mode)) {
		error = git_odb__hashlink(out, full_path.ptr);
		diff->base.perf.oid_calculations++;
	} else if (!git__is_sizet(entry.file_size)) {
		git_error_set(GIT_ERROR_NOMEMORY, "file size overflow (for 32-bits) on '%s'",
			entry.path);
		error = -1;
	} else if (!(error = git_filter_list_load(&fl,
		diff->base.repo, NULL, entry.path,
		GIT_FILTER_TO_ODB, GIT_FILTER_ALLOW_UNSAFE)))
	{
		int fd = git_futils_open_ro(full_path.ptr);
		if (fd < 0)
			error = fd;
		else {
			error = git_odb__hashfd_filtered(
				out, fd, (size_t)entry.file_size, GIT_OBJECT_BLOB, fl);
			p_close(fd);
			diff->base.perf.oid_calculations++;
		}

		git_filter_list_free(fl);
	}

	/* update index for entry if requested */
	if (!error && update_match && git_oid_equal(out, update_match)) {
		git_index *idx;
		git_index_entry updated_entry;

		memcpy(&updated_entry, &entry, sizeof(git_index_entry));
		updated_entry.mode = mode;
		git_oid_cpy(&updated_entry.id, out);

		if (!(error = git_repository_index__weakptr(&idx,
			diff->base.repo))) {
			error = git_index_add(idx, &updated_entry);
			diff->index_updated = true;
		}
 	}

	git_buf_dispose(&full_path);
	return error;
}