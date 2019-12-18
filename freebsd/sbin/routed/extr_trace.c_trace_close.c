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
struct TYPE_2__ {scalar_t__ tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  _PATH_DEVNULL ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ftrace ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 TYPE_1__ lastlog_time ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdout ; 

void
trace_close(int zap_stdio)
{
	int fd;


	fflush(stdout);
	fflush(stderr);

	if (ftrace != NULL && zap_stdio) {
		if (ftrace != stdout)
			fclose(ftrace);
		ftrace = NULL;
		fd = open(_PATH_DEVNULL, O_RDWR);
		if (fd < 0)
			return;
		if (isatty(STDIN_FILENO))
			(void)dup2(fd, STDIN_FILENO);
		if (isatty(STDOUT_FILENO))
			(void)dup2(fd, STDOUT_FILENO);
		if (isatty(STDERR_FILENO))
			(void)dup2(fd, STDERR_FILENO);
		(void)close(fd);
	}
	lastlog_time.tv_sec = 0;
}