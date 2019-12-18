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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ fork () ; 
 int net_write (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pipe_a_like (int*) ; 
 int /*<<< orphan*/  rshd_loop (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
setup_copier (int have_errsock)
{
    int p0[2], p1[2], p2[2];
    pid_t pid;

    pipe_a_like(p0);
    pipe_a_like(p1);
    pipe_a_like(p2);
    pid = fork ();
    if (pid < 0)
	fatal (STDOUT_FILENO, "fork", "Could not create child process.");
    if (pid == 0) { /* child */
	close (p0[1]);
	close (p1[0]);
	close (p2[0]);
	dup2 (p0[0], STDIN_FILENO);
	dup2 (p1[1], STDOUT_FILENO);
	dup2 (p2[1], STDERR_FILENO);
	close (p0[0]);
	close (p1[1]);
	close (p2[1]);
    } else { /* parent */
	close (p0[0]);
	close (p1[1]);
	close (p2[1]);

	if (net_write (STDOUT_FILENO, "", 1) != 1)
	    fatal (STDOUT_FILENO, "net_write", "Write failure.");

	rshd_loop (STDIN_FILENO, p0[1],
	      STDOUT_FILENO, p1[0],
	      STDERR_FILENO, p2[0],
	      have_errsock);
    }
}