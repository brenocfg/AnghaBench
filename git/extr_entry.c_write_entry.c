#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct submodule {int dummy; } ;
struct stream_filter {int dummy; } ;
struct strbuf {int dummy; } ;
struct stat {int dummy; } ;
struct delayed_checkout {int /*<<< orphan*/  paths; int /*<<< orphan*/  state; } ;
struct checkout {TYPE_1__* istate; scalar_t__ refresh_cache; int /*<<< orphan*/  force; struct delayed_checkout* delayed_checkout; } ;
struct cache_entry {unsigned int ce_mode; char* name; int /*<<< orphan*/  ce_flags; int /*<<< orphan*/  oid; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_7__ {int /*<<< orphan*/  cache_changed; } ;

/* Variables and functions */
 int /*<<< orphan*/  CE_ENTRY_CHANGED ; 
 int /*<<< orphan*/  CE_NO_DELAY ; 
 int /*<<< orphan*/  CE_RETRY ; 
 int /*<<< orphan*/  CE_UPDATE_IN_BASE ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  SUBMODULE_MOVE_HEAD_FORCE ; 
#define  S_IFGITLINK 130 
#define  S_IFLNK 129 
 unsigned int S_IFMT ; 
#define  S_IFREG 128 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int async_convert_to_working_tree (TYPE_1__*,char*,char*,unsigned long,struct strbuf*,struct delayed_checkout*) ; 
 int /*<<< orphan*/  close (int) ; 
 int convert_to_working_tree (TYPE_1__*,char*,char*,unsigned long,struct strbuf*) ; 
 int error (char*,char*,...) ; 
 int error_errno (char*,char*) ; 
 int /*<<< orphan*/  fill_stat_cache_info (TYPE_1__*,struct cache_entry*,struct stat*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fstat_output (int,struct checkout const*,struct stat*) ; 
 struct stream_filter* get_stream_filter (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  has_symlinks ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 int /*<<< orphan*/  mark_fsmonitor_invalid (TYPE_1__*,struct cache_entry*) ; 
 int /*<<< orphan*/  mkdir (char*,int) ; 
 char* oid_to_hex (int /*<<< orphan*/ *) ; 
 int open_output_fd (char*,struct cache_entry*,int) ; 
 char* read_blob_entry (struct cache_entry*,unsigned long*) ; 
 char* strbuf_detach (struct strbuf*,size_t*) ; 
 int /*<<< orphan*/  streaming_write_entry (struct cache_entry*,char*,struct stream_filter*,struct checkout const*,int,int*,struct stat*) ; 
 int /*<<< orphan*/  string_list_has_string (int /*<<< orphan*/ *,char*) ; 
 struct submodule* submodule_from_ce (struct cache_entry*) ; 
 int submodule_move_head (char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int symlink (char*,char*) ; 
 int /*<<< orphan*/  write_in_full (int,char*,unsigned long) ; 

__attribute__((used)) static int write_entry(struct cache_entry *ce,
		       char *path, const struct checkout *state, int to_tempfile)
{
	unsigned int ce_mode_s_ifmt = ce->ce_mode & S_IFMT;
	struct delayed_checkout *dco = state->delayed_checkout;
	int fd, ret, fstat_done = 0;
	char *new_blob;
	struct strbuf buf = STRBUF_INIT;
	unsigned long size;
	ssize_t wrote;
	size_t newsize = 0;
	struct stat st;
	const struct submodule *sub;

	if (ce_mode_s_ifmt == S_IFREG) {
		struct stream_filter *filter = get_stream_filter(state->istate, ce->name,
								 &ce->oid);
		if (filter &&
		    !streaming_write_entry(ce, path, filter,
					   state, to_tempfile,
					   &fstat_done, &st))
			goto finish;
	}

	switch (ce_mode_s_ifmt) {
	case S_IFLNK:
		new_blob = read_blob_entry(ce, &size);
		if (!new_blob)
			return error("unable to read sha1 file of %s (%s)",
				     path, oid_to_hex(&ce->oid));

		/*
		 * We can't make a real symlink; write out a regular file entry
		 * with the symlink destination as its contents.
		 */
		if (!has_symlinks || to_tempfile)
			goto write_file_entry;

		ret = symlink(new_blob, path);
		free(new_blob);
		if (ret)
			return error_errno("unable to create symlink %s", path);
		break;

	case S_IFREG:
		/*
		 * We do not send the blob in case of a retry, so do not
		 * bother reading it at all.
		 */
		if (dco && dco->state == CE_RETRY) {
			new_blob = NULL;
			size = 0;
		} else {
			new_blob = read_blob_entry(ce, &size);
			if (!new_blob)
				return error("unable to read sha1 file of %s (%s)",
					     path, oid_to_hex(&ce->oid));
		}

		/*
		 * Convert from git internal format to working tree format
		 */
		if (dco && dco->state != CE_NO_DELAY) {
			ret = async_convert_to_working_tree(state->istate, ce->name, new_blob,
							    size, &buf, dco);
			if (ret && string_list_has_string(&dco->paths, ce->name)) {
				free(new_blob);
				goto delayed;
			}
		} else
			ret = convert_to_working_tree(state->istate, ce->name, new_blob, size, &buf);

		if (ret) {
			free(new_blob);
			new_blob = strbuf_detach(&buf, &newsize);
			size = newsize;
		}
		/*
		 * No "else" here as errors from convert are OK at this
		 * point. If the error would have been fatal (e.g.
		 * filter is required), then we would have died already.
		 */

	write_file_entry:
		fd = open_output_fd(path, ce, to_tempfile);
		if (fd < 0) {
			free(new_blob);
			return error_errno("unable to create file %s", path);
		}

		wrote = write_in_full(fd, new_blob, size);
		if (!to_tempfile)
			fstat_done = fstat_output(fd, state, &st);
		close(fd);
		free(new_blob);
		if (wrote < 0)
			return error("unable to write file %s", path);
		break;

	case S_IFGITLINK:
		if (to_tempfile)
			return error("cannot create temporary submodule %s", path);
		if (mkdir(path, 0777) < 0)
			return error("cannot create submodule directory %s", path);
		sub = submodule_from_ce(ce);
		if (sub)
			return submodule_move_head(ce->name,
				NULL, oid_to_hex(&ce->oid),
				state->force ? SUBMODULE_MOVE_HEAD_FORCE : 0);
		break;

	default:
		return error("unknown file mode for %s in index", path);
	}

finish:
	if (state->refresh_cache) {
		assert(state->istate);
		if (!fstat_done)
			if (lstat(ce->name, &st) < 0)
				return error_errno("unable to stat just-written file %s",
						   ce->name);
		fill_stat_cache_info(state->istate, ce, &st);
		ce->ce_flags |= CE_UPDATE_IN_BASE;
		mark_fsmonitor_invalid(state->istate, ce);
		state->istate->cache_changed |= CE_ENTRY_CHANGED;
	}
delayed:
	return 0;
}