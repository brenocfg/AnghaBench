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
struct strbuf {size_t len; scalar_t__ buf; } ;
struct repository_format {int dummy; } ;

/* Variables and functions */
 struct repository_format REPOSITORY_FORMAT_INIT ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  clear_repository_format (struct repository_format*) ; 
 int /*<<< orphan*/  get_common_dir (struct strbuf*,scalar_t__) ; 
 int /*<<< orphan*/  is_absolute_path (scalar_t__) ; 
 int /*<<< orphan*/  read_repository_format (struct repository_format*,scalar_t__) ; 
 scalar_t__ setup_git_directory_gently_1 (struct strbuf*,struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,scalar_t__) ; 
 scalar_t__ strbuf_getcwd (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_insert (struct strbuf*,size_t,scalar_t__,size_t) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,size_t) ; 
 int /*<<< orphan*/  strcmp (char*,scalar_t__) ; 
 scalar_t__ verify_repository_format (struct repository_format*,struct strbuf*) ; 
 int /*<<< orphan*/  warning (char*,scalar_t__,scalar_t__) ; 

int discover_git_directory(struct strbuf *commondir,
			   struct strbuf *gitdir)
{
	struct strbuf dir = STRBUF_INIT, err = STRBUF_INIT;
	size_t gitdir_offset = gitdir->len, cwd_len;
	size_t commondir_offset = commondir->len;
	struct repository_format candidate = REPOSITORY_FORMAT_INIT;

	if (strbuf_getcwd(&dir))
		return -1;

	cwd_len = dir.len;
	if (setup_git_directory_gently_1(&dir, gitdir, 0) <= 0) {
		strbuf_release(&dir);
		return -1;
	}

	/*
	 * The returned gitdir is relative to dir, and if dir does not reflect
	 * the current working directory, we simply make the gitdir absolute.
	 */
	if (dir.len < cwd_len && !is_absolute_path(gitdir->buf + gitdir_offset)) {
		/* Avoid a trailing "/." */
		if (!strcmp(".", gitdir->buf + gitdir_offset))
			strbuf_setlen(gitdir, gitdir_offset);
		else
			strbuf_addch(&dir, '/');
		strbuf_insert(gitdir, gitdir_offset, dir.buf, dir.len);
	}

	get_common_dir(commondir, gitdir->buf + gitdir_offset);

	strbuf_reset(&dir);
	strbuf_addf(&dir, "%s/config", commondir->buf + commondir_offset);
	read_repository_format(&candidate, dir.buf);
	strbuf_release(&dir);

	if (verify_repository_format(&candidate, &err) < 0) {
		warning("ignoring git dir '%s': %s",
			gitdir->buf + gitdir_offset, err.buf);
		strbuf_release(&err);
		strbuf_setlen(commondir, commondir_offset);
		strbuf_setlen(gitdir, gitdir_offset);
		clear_repository_format(&candidate);
		return -1;
	}

	clear_repository_format(&candidate);
	return 0;
}