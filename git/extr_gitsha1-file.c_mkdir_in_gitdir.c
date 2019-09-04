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
struct strbuf {char const* buf; } ;
struct stat {int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int EEXIST ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  S_ISLNK (int /*<<< orphan*/ ) ; 
 int adjust_shared_perm (char const*) ; 
 int errno ; 
 int /*<<< orphan*/  is_absolute_path (char const*) ; 
 scalar_t__ lstat (char const*,struct stat*) ; 
 scalar_t__ mkdir (char const*,int) ; 
 scalar_t__ strbuf_readlink (struct strbuf*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

int mkdir_in_gitdir(const char *path)
{
	if (mkdir(path, 0777)) {
		int saved_errno = errno;
		struct stat st;
		struct strbuf sb = STRBUF_INIT;

		if (errno != EEXIST)
			return -1;
		/*
		 * Are we looking at a path in a symlinked worktree
		 * whose original repository does not yet have it?
		 * e.g. .git/rr-cache pointing at its original
		 * repository in which the user hasn't performed any
		 * conflict resolution yet?
		 */
		if (lstat(path, &st) || !S_ISLNK(st.st_mode) ||
		    strbuf_readlink(&sb, path, st.st_size) ||
		    !is_absolute_path(sb.buf) ||
		    mkdir(sb.buf, 0777)) {
			strbuf_release(&sb);
			errno = saved_errno;
			return -1;
		}
		strbuf_release(&sb);
	}
	return adjust_shared_perm(path);
}