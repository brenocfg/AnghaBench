#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct stat {scalar_t__ st_mode; } ;
struct TYPE_8__ {int /*<<< orphan*/  stat_calls; int /*<<< orphan*/  mkdir_calls; } ;
struct git_futils_mkdir_options {TYPE_1__ perfdata; scalar_t__ dir_map; scalar_t__ pool; int /*<<< orphan*/  member_0; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  mode_t ;
struct TYPE_9__ {scalar_t__ size; char* ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 scalar_t__ ENOENT ; 
 TYPE_2__ GIT_BUF_INIT ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (char*) ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_ADD (size_t*,scalar_t__,int) ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int GIT_MKDIR_PATH ; 
 int GIT_MKDIR_VERIFY_DIR ; 
 int /*<<< orphan*/  S_ISDIR (scalar_t__) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 size_t git_buf_rfind (TYPE_2__*,char) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ git_path_join_unrooted (TYPE_2__*,char const*,char const*,size_t*) ; 
 size_t git_path_root (char*) ; 
 char* git_pool_malloc (scalar_t__,size_t) ; 
 scalar_t__ git_strmap_exists (scalar_t__,char*) ; 
 int git_strmap_set (scalar_t__,char*,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,scalar_t__) ; 
 int mkdir_canonicalize (TYPE_2__*,int) ; 
 int mkdir_validate_dir (char*,struct stat*,int /*<<< orphan*/ ,int,struct git_futils_mkdir_options*) ; 
 int mkdir_validate_mode (char*,struct stat*,int,int /*<<< orphan*/ ,int,struct git_futils_mkdir_options*) ; 
 scalar_t__ p_lstat (char*,struct stat*) ; 
 scalar_t__ p_mkdir (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ p_stat (char*,struct stat*) ; 

int git_futils_mkdir_relative(
	const char *relative_path,
	const char *base,
	mode_t mode,
	uint32_t flags,
	struct git_futils_mkdir_options *opts)
{
	git_buf make_path = GIT_BUF_INIT;
	ssize_t root = 0, min_root_len;
	char lastch = '/', *tail;
	struct stat st;
	struct git_futils_mkdir_options empty_opts = {0};
	int error;

	if (!opts)
		opts = &empty_opts;

	/* build path and find "root" where we should start calling mkdir */
	if (git_path_join_unrooted(&make_path, relative_path, base, &root) < 0)
		return -1;

	if ((error = mkdir_canonicalize(&make_path, flags)) < 0 ||
		make_path.size == 0)
		goto done;

	/* if we are not supposed to make the whole path, reset root */
	if ((flags & GIT_MKDIR_PATH) == 0)
		root = git_buf_rfind(&make_path, '/');

	/* advance root past drive name or network mount prefix */
	min_root_len = git_path_root(make_path.ptr);
	if (root < min_root_len)
		root = min_root_len;
	while (root >= 0 && make_path.ptr[root] == '/')
		++root;

	/* clip root to make_path length */
	if (root > (ssize_t)make_path.size)
		root = (ssize_t)make_path.size; /* i.e. NUL byte of string */
	if (root < 0)
		root = 0;

	/* walk down tail of path making each directory */
	for (tail = &make_path.ptr[root]; *tail; *tail = lastch) {
		bool mkdir_attempted = false;

		/* advance tail to include next path component */
		while (*tail == '/')
			tail++;
		while (*tail && *tail != '/')
			tail++;

		/* truncate path at next component */
		lastch = *tail;
		*tail = '\0';
		st.st_mode = 0;

		if (opts->dir_map && git_strmap_exists(opts->dir_map, make_path.ptr))
			continue;

		/* See what's going on with this path component */
		opts->perfdata.stat_calls++;

retry_lstat:
		if (p_lstat(make_path.ptr, &st) < 0) {
			if (mkdir_attempted || errno != ENOENT) {
				git_error_set(GIT_ERROR_OS, "cannot access component in path '%s'", make_path.ptr);
				error = -1;
				goto done;
			}

			git_error_clear();
			opts->perfdata.mkdir_calls++;
			mkdir_attempted = true;
			if (p_mkdir(make_path.ptr, mode) < 0) {
				if (errno == EEXIST)
					goto retry_lstat;
				git_error_set(GIT_ERROR_OS, "failed to make directory '%s'", make_path.ptr);
				error = -1;
				goto done;
			}
		} else {
			if ((error = mkdir_validate_dir(
				make_path.ptr, &st, mode, flags, opts)) < 0)
				goto done;
		}

		/* chmod if requested and necessary */
		if ((error = mkdir_validate_mode(
			make_path.ptr, &st, (lastch == '\0'), mode, flags, opts)) < 0)
			goto done;

		if (opts->dir_map && opts->pool) {
			char *cache_path;
			size_t alloc_size;

			GIT_ERROR_CHECK_ALLOC_ADD(&alloc_size, make_path.size, 1);
			cache_path = git_pool_malloc(opts->pool, alloc_size);
			GIT_ERROR_CHECK_ALLOC(cache_path);

			memcpy(cache_path, make_path.ptr, make_path.size + 1);

			if ((error = git_strmap_set(opts->dir_map, cache_path, cache_path)) < 0)
				goto done;
		}
	}

	error = 0;

	/* check that full path really is a directory if requested & needed */
	if ((flags & GIT_MKDIR_VERIFY_DIR) != 0 &&
		lastch != '\0') {
		opts->perfdata.stat_calls++;

		if (p_stat(make_path.ptr, &st) < 0 || !S_ISDIR(st.st_mode)) {
			git_error_set(GIT_ERROR_OS, "path is not a directory '%s'",
				make_path.ptr);
			error = GIT_ENOTFOUND;
		}
	}

done:
	git_buf_dispose(&make_path);
	return error;
}