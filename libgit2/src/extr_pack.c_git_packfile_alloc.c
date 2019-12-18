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
struct stat {scalar_t__ st_mtime; int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_mode; } ;
struct TYPE_2__ {int fd; int /*<<< orphan*/  size; } ;
struct git_pack_file {int pack_keep; int pack_local; int index_version; int /*<<< orphan*/  bases; int /*<<< orphan*/  lock; scalar_t__ mtime; TYPE_1__ mwf; scalar_t__ pack_name; } ;
typedef  scalar_t__ git_time_t ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (struct git_pack_file*) ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_ADD (size_t*,size_t,int) ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ cache_init (int /*<<< orphan*/ *) ; 
 struct git_pack_file* git__calloc (int,size_t) ; 
 int /*<<< orphan*/  git__free (struct git_pack_file*) ; 
 scalar_t__ git__suffixcmp (char const*,char*) ; 
 int /*<<< orphan*/  git_disable_pack_keep_file_checks ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_mutex_init (int /*<<< orphan*/ *) ; 
 int git_odb__error_notfound (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_path_exists (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,int) ; 
 scalar_t__ p_stat (scalar_t__,struct stat*) ; 
 size_t strlen (char const*) ; 

int git_packfile_alloc(struct git_pack_file **pack_out, const char *path)
{
	struct stat st;
	struct git_pack_file *p;
	size_t path_len = path ? strlen(path) : 0, alloc_len;

	*pack_out = NULL;

	if (path_len < strlen(".idx"))
		return git_odb__error_notfound("invalid packfile path", NULL, 0);

	GIT_ERROR_CHECK_ALLOC_ADD(&alloc_len, sizeof(*p), path_len);
	GIT_ERROR_CHECK_ALLOC_ADD(&alloc_len, alloc_len, 2);

	p = git__calloc(1, alloc_len);
	GIT_ERROR_CHECK_ALLOC(p);

	memcpy(p->pack_name, path, path_len + 1);

	/*
	 * Make sure a corresponding .pack file exists and that
	 * the index looks sane.
	 */
	if (git__suffixcmp(path, ".idx") == 0) {
		size_t root_len = path_len - strlen(".idx");

		if (!git_disable_pack_keep_file_checks) {
			memcpy(p->pack_name + root_len, ".keep", sizeof(".keep"));
			if (git_path_exists(p->pack_name) == true)
				p->pack_keep = 1;
		}

		memcpy(p->pack_name + root_len, ".pack", sizeof(".pack"));
	}

	if (p_stat(p->pack_name, &st) < 0 || !S_ISREG(st.st_mode)) {
		git__free(p);
		return git_odb__error_notfound("packfile not found", NULL, 0);
	}

	/* ok, it looks sane as far as we can check without
	 * actually mapping the pack file.
	 */
	p->mwf.fd = -1;
	p->mwf.size = st.st_size;
	p->pack_local = 1;
	p->mtime = (git_time_t)st.st_mtime;
	p->index_version = -1;

	if (git_mutex_init(&p->lock)) {
		git_error_set(GIT_ERROR_OS, "failed to initialize packfile mutex");
		git__free(p);
		return -1;
	}

	if (cache_init(&p->bases) < 0) {
		git__free(p);
		return -1;
	}

	*pack_out = p;

	return 0;
}