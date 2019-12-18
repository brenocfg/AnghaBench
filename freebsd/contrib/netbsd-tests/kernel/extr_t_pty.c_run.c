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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 scalar_t__ WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 size_t buffer_size ; 
 size_t* calloc (int,size_t) ; 
 int /*<<< orphan*/  child_spawn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 size_t* dbuf ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 size_t packets ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  ptsname (int) ; 
 int pty_open () ; 
 int /*<<< orphan*/  sleep (int) ; 
 scalar_t__ verbose ; 
 int waitpid (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int write (int,size_t*,size_t) ; 

__attribute__((used)) static
void run(void)
{
	size_t i;
	int pty;
	int status;
	pid_t child;
	if ((dbuf = calloc(1, buffer_size)) == NULL)
		err(EXIT_FAILURE, "malloc(%zu)", buffer_size);

	if (verbose)
		(void)printf(
		    "parent: started; opening PTY and spawning child\n");
	pty = pty_open();
	child = child_spawn(ptsname(pty));
	if (verbose)
		(void)printf("parent: sleeping to make sure child is ready\n");
	(void)sleep(1);

	for (i = 0; i < buffer_size; i++)
		dbuf[i] = i & 0xff;

	if (verbose)
		(void)printf("parent: writing\n");

	for (i = 0; i < packets; i++) {
		ssize_t	size;

		if (verbose)
			(void)printf(
			    "parent: attempting to write %zu bytes to PTY\n",
			    buffer_size);
		if ((size = write(pty, dbuf, buffer_size)) == -1) {
			err(EXIT_FAILURE, "parent: write()");
			break;
		}
		if (verbose)
			(void)printf("parent: wrote %zd bytes to PTY\n", size);
	}

	if (verbose)
		(void)printf("parent: waiting for child to exit\n");
	if (waitpid(child, &status, 0) == -1)
		err(EXIT_FAILURE, "waitpid");
	if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
		errx(EXIT_FAILURE, "child failed");

	if (verbose)
		(void)printf("parent: closing PTY\n");
	(void)close(pty);
	if (verbose)
		(void)printf("parent: exiting\n");
}