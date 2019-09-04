#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stat {scalar_t__ st_size; } ;
struct TYPE_5__ {int /*<<< orphan*/  path; int /*<<< orphan*/  stamp; } ;
typedef  TYPE_1__ git_sortedcache ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  git__is_sizet (scalar_t__) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int git_futils_filestamp_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_futils_open_ro (int /*<<< orphan*/ ) ; 
 int git_futils_readbuffer_fd (int /*<<< orphan*/ *,int,size_t) ; 
 int git_sortedcache_wlock (TYPE_1__*) ; 
 int /*<<< orphan*/  git_sortedcache_wunlock (TYPE_1__*) ; 
 int /*<<< orphan*/  p_close (int) ; 
 scalar_t__ p_fstat (int,struct stat*) ; 

int git_sortedcache_lockandload(git_sortedcache *sc, git_buf *buf)
{
	int error, fd;
	struct stat st;

	if ((error = git_sortedcache_wlock(sc)) < 0)
		return error;

	if ((error = git_futils_filestamp_check(&sc->stamp, sc->path)) <= 0)
		goto unlock;

	if ((fd = git_futils_open_ro(sc->path)) < 0) {
		error = fd;
		goto unlock;
	}

	if (p_fstat(fd, &st) < 0) {
		git_error_set(GIT_ERROR_OS, "failed to stat file");
		error = -1;
		(void)p_close(fd);
		goto unlock;
	}

	if (!git__is_sizet(st.st_size)) {
		git_error_set(GIT_ERROR_INVALID, "unable to load file larger than size_t");
		error = -1;
		(void)p_close(fd);
		goto unlock;
	}

	if (buf)
		error = git_futils_readbuffer_fd(buf, fd, (size_t)st.st_size);

	(void)p_close(fd);

	if (error < 0)
		goto unlock;

	return 1; /* return 1 -> file needs reload and was successfully loaded */

unlock:
	git_sortedcache_wunlock(sc);
	return error;
}