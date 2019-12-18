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
struct program_filter {int child_stdin; int child_stdout; scalar_t__ child; int waitpid_return; int /*<<< orphan*/  exit_status; } ;
struct archive_read_filter {TYPE_1__* archive; } ;
struct TYPE_2__ {int /*<<< orphan*/  archive; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ EINTR ; 
 scalar_t__ SIGPIPE ; 
 scalar_t__ WEXITSTATUS (int /*<<< orphan*/ ) ; 
 scalar_t__ WIFEXITED (int /*<<< orphan*/ ) ; 
 scalar_t__ WIFSIGNALED (int /*<<< orphan*/ ) ; 
 scalar_t__ WTERMSIG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int waitpid (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
child_stop(struct archive_read_filter *self, struct program_filter *state)
{
	/* Close our side of the I/O with the child. */
	if (state->child_stdin != -1) {
		close(state->child_stdin);
		state->child_stdin = -1;
	}
	if (state->child_stdout != -1) {
		close(state->child_stdout);
		state->child_stdout = -1;
	}

	if (state->child != 0) {
		/* Reap the child. */
		do {
			state->waitpid_return
			    = waitpid(state->child, &state->exit_status, 0);
		} while (state->waitpid_return == -1 && errno == EINTR);
#if defined(_WIN32) && !defined(__CYGWIN__)
		CloseHandle(state->child);
#endif
		state->child = 0;
	}

	if (state->waitpid_return < 0) {
		/* waitpid() failed?  This is ugly. */
		archive_set_error(&self->archive->archive, ARCHIVE_ERRNO_MISC,
		    "Child process exited badly");
		return (ARCHIVE_WARN);
	}

#if !defined(_WIN32) || defined(__CYGWIN__)
	if (WIFSIGNALED(state->exit_status)) {
#ifdef SIGPIPE
		/* If the child died because we stopped reading before
		 * it was done, that's okay.  Some archive formats
		 * have padding at the end that we routinely ignore. */
		/* The alternative to this would be to add a step
		 * before close(child_stdout) above to read from the
		 * child until the child has no more to write. */
		if (WTERMSIG(state->exit_status) == SIGPIPE)
			return (ARCHIVE_OK);
#endif
		archive_set_error(&self->archive->archive, ARCHIVE_ERRNO_MISC,
		    "Child process exited with signal %d",
		    WTERMSIG(state->exit_status));
		return (ARCHIVE_WARN);
	}
#endif /* !_WIN32 || __CYGWIN__ */

	if (WIFEXITED(state->exit_status)) {
		if (WEXITSTATUS(state->exit_status) == 0)
			return (ARCHIVE_OK);

		archive_set_error(&self->archive->archive,
		    ARCHIVE_ERRNO_MISC,
		    "Child process exited with status %d",
		    WEXITSTATUS(state->exit_status));
		return (ARCHIVE_WARN);
	}

	return (ARCHIVE_WARN);
}