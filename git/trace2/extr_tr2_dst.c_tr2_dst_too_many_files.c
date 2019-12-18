#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tr2_dst {int too_many_files; int /*<<< orphan*/  fd; } ;
struct strbuf {int len; int /*<<< orphan*/ * buf; } ;
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 char const* DISCARD_SENTINEL_NAME ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_WRONLY ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  TR2_SYSENV_MAX_FILES ; 
 int atoi (char const*) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_dir_sep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * opendir (int /*<<< orphan*/ *) ; 
 scalar_t__ readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stat (int /*<<< orphan*/ *,struct stat*) ; 
 int /*<<< orphan*/  strbuf_addbuf (struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 char* tr2_sysenv_get (int /*<<< orphan*/ ) ; 
 int tr2env_max_files ; 

__attribute__((used)) static int tr2_dst_too_many_files(struct tr2_dst *dst, const char *tgt_prefix)
{
	int file_count = 0, max_files = 0, ret = 0;
	const char *max_files_var;
	DIR *dirp;
	struct strbuf path = STRBUF_INIT, sentinel_path = STRBUF_INIT;
	struct stat statbuf;

	/* Get the config or envvar and decide if we should continue this check */
	max_files_var = tr2_sysenv_get(TR2_SYSENV_MAX_FILES);
	if (max_files_var && *max_files_var && ((max_files = atoi(max_files_var)) >= 0))
		tr2env_max_files = max_files;

	if (!tr2env_max_files) {
		ret = 0;
		goto cleanup;
	}

	strbuf_addstr(&path, tgt_prefix);
	if (!is_dir_sep(path.buf[path.len - 1])) {
		strbuf_addch(&path, '/');
	}

	/* check sentinel */
	strbuf_addbuf(&sentinel_path, &path);
	strbuf_addstr(&sentinel_path, DISCARD_SENTINEL_NAME);
	if (!stat(sentinel_path.buf, &statbuf)) {
		ret = 1;
		goto cleanup;
	}

	/* check file count */
	dirp = opendir(path.buf);
	while (file_count < tr2env_max_files && dirp && readdir(dirp))
		file_count++;
	if (dirp)
		closedir(dirp);

	if (file_count >= tr2env_max_files) {
		dst->too_many_files = 1;
		dst->fd = open(sentinel_path.buf, O_WRONLY | O_CREAT | O_EXCL, 0666);
		ret = -1;
		goto cleanup;
	}

cleanup:
	strbuf_release(&path);
	strbuf_release(&sentinel_path);
	return ret;
}