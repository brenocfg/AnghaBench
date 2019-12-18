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
struct program_filter {int child_stdin; int /*<<< orphan*/  child_stdout; } ;
struct archive_read_filter {int /*<<< orphan*/  upstream; struct program_filter* data; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ EPIPE ; 
 int /*<<< orphan*/  F_SETFL ; 
 scalar_t__ PeekNamedPipe (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 size_t SSIZE_MAX ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  __archive_check_child (int,int /*<<< orphan*/ ) ; 
 char* __archive_read_filter_ahead (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  __archive_read_filter_consume (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _get_osfhandle (int /*<<< orphan*/ ) ; 
 int child_stop (struct archive_read_filter*,struct program_filter*) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 int write (int,char const*,int) ; 

__attribute__((used)) static ssize_t
child_read(struct archive_read_filter *self, char *buf, size_t buf_len)
{
	struct program_filter *state = self->data;
	ssize_t ret, requested, avail;
	const char *p;
#if defined(_WIN32) && !defined(__CYGWIN__)
	HANDLE handle = (HANDLE)_get_osfhandle(state->child_stdout);
#endif

	requested = buf_len > SSIZE_MAX ? SSIZE_MAX : buf_len;

	for (;;) {
		do {
#if defined(_WIN32) && !defined(__CYGWIN__)
			/* Avoid infinity wait.
			 * Note: If there is no data in the pipe, ReadFile()
			 * called in read() never returns and so we won't
			 * write remaining encoded data to the pipe.
			 * Note: This way may cause performance problem.
			 * we are looking forward to great code to resolve
			 * this.  */
			DWORD pipe_avail = -1;
			int cnt = 2;

			while (PeekNamedPipe(handle, NULL, 0, NULL,
			    &pipe_avail, NULL) != 0 && pipe_avail == 0 &&
			    cnt--)
				Sleep(5);
			if (pipe_avail == 0) {
				ret = -1;
				errno = EAGAIN;
				break;
			}
#endif
			ret = read(state->child_stdout, buf, requested);
		} while (ret == -1 && errno == EINTR);

		if (ret > 0)
			return (ret);
		if (ret == 0 || (ret == -1 && errno == EPIPE))
			/* Child has closed its output; reap the child
			 * and return the status. */
			return (child_stop(self, state));
		if (ret == -1 && errno != EAGAIN)
			return (-1);

		if (state->child_stdin == -1) {
			/* Block until child has some I/O ready. */
			__archive_check_child(state->child_stdin,
			    state->child_stdout);
			continue;
		}

		/* Get some more data from upstream. */
		p = __archive_read_filter_ahead(self->upstream, 1, &avail);
		if (p == NULL) {
			close(state->child_stdin);
			state->child_stdin = -1;
			fcntl(state->child_stdout, F_SETFL, 0);
			if (avail < 0)
				return (avail);
			continue;
		}

		do {
			ret = write(state->child_stdin, p, avail);
		} while (ret == -1 && errno == EINTR);

		if (ret > 0) {
			/* Consume whatever we managed to write. */
			__archive_read_filter_consume(self->upstream, ret);
		} else if (ret == -1 && errno == EAGAIN) {
			/* Block until child has some I/O ready. */
			__archive_check_child(state->child_stdin,
			    state->child_stdout);
		} else {
			/* Write failed. */
			close(state->child_stdin);
			state->child_stdin = -1;
			fcntl(state->child_stdout, F_SETFL, 0);
			/* If it was a bad error, we're done; otherwise
			 * it was EPIPE or EOF, and we can still read
			 * from the child. */
			if (ret == -1 && errno != EPIPE)
				return (-1);
		}
	}
}