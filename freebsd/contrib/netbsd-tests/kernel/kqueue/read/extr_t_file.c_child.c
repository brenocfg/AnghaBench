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

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  FILENAME ; 
 int NLINES ; 
 int O_APPEND ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int write (int,char*,int) ; 

__attribute__((used)) static void
child(void)
{
	int i, n, fd;

	(void)sleep(1);

	for (i = 0; i < NLINES; ++i) {
		fd = open(FILENAME, O_WRONLY|O_APPEND, 0644);
		if (fd < 0)
			err(EXIT_FAILURE, "open()");

		n = write(fd, "foo\n", 4);
		if (n < 0)
			err(EXIT_FAILURE, "write()");

		(void)close(fd);
		(void)sleep(1);
	}
	_exit(0);
}