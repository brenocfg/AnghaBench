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
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execl (char*,char*,char*,char*,char*) ; 
 scalar_t__ open (char*,int) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpd_warn (char*) ; 

__attribute__((used)) static void do_child(char *command)
{
    char   *error;
    int     tmp_fd;

    /*
     * Systems with POSIX sessions may send a SIGHUP to grandchildren if the
     * child exits first. This is sick, sessions were invented for terminals.
     */

    signal(SIGHUP, SIG_IGN);

    /* Set up new stdin, stdout, stderr, and exec the shell command. */

    for (tmp_fd = 0; tmp_fd < 3; tmp_fd++)
	(void) close(tmp_fd);
    if (open("/dev/null", 2) != 0) {
	error = "open /dev/null: %m";
    } else if (dup(0) != 1 || dup(0) != 2) {
	error = "dup: %m";
    } else {
	(void) execl("/bin/sh", "sh", "-c", command, (char *) 0);
	error = "execl /bin/sh: %m";
    }

    /* Something went wrong. We MUST terminate the child process. */

    tcpd_warn(error);
    _exit(0);
}