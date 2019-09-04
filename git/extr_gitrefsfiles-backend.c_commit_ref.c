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
struct strbuf {int dummy; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct ref_lock {int /*<<< orphan*/  lk; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ commit_lock_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_locked_file_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstat (char*,struct stat*) ; 
 int /*<<< orphan*/  remove_empty_directories (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_attach (struct strbuf*,char*,size_t,size_t) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int commit_ref(struct ref_lock *lock)
{
	char *path = get_locked_file_path(&lock->lk);
	struct stat st;

	if (!lstat(path, &st) && S_ISDIR(st.st_mode)) {
		/*
		 * There is a directory at the path we want to rename
		 * the lockfile to. Hopefully it is empty; try to
		 * delete it.
		 */
		size_t len = strlen(path);
		struct strbuf sb_path = STRBUF_INIT;

		strbuf_attach(&sb_path, path, len, len);

		/*
		 * If this fails, commit_lock_file() will also fail
		 * and will report the problem.
		 */
		remove_empty_directories(&sb_path);
		strbuf_release(&sb_path);
	} else {
		free(path);
	}

	if (commit_lock_file(&lock->lk))
		return -1;
	return 0;
}