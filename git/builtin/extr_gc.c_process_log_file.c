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
struct TYPE_5__ {int /*<<< orphan*/  tempfile; } ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  commit_lock_file (TYPE_1__*) ; 
 int errno ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  get_lock_file_fd (TYPE_1__*) ; 
 char* get_tempfile_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path (char*) ; 
 TYPE_1__ log_lock ; 
 int /*<<< orphan*/  rollback_lock_file (TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process_log_file(void)
{
	struct stat st;
	if (fstat(get_lock_file_fd(&log_lock), &st)) {
		/*
		 * Perhaps there was an i/o error or another
		 * unlikely situation.  Try to make a note of
		 * this in gc.log along with any existing
		 * messages.
		 */
		int saved_errno = errno;
		fprintf(stderr, _("Failed to fstat %s: %s"),
			get_tempfile_path(log_lock.tempfile),
			strerror(saved_errno));
		fflush(stderr);
		commit_lock_file(&log_lock);
		errno = saved_errno;
	} else if (st.st_size) {
		/* There was some error recorded in the lock file */
		commit_lock_file(&log_lock);
	} else {
		/* No error, clean up any old gc.log */
		unlink(git_path("gc.log"));
		rollback_lock_file(&log_lock);
	}
}