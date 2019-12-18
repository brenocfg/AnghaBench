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
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  PF_UNIX ; 
 int SOCK_NONBLOCK ; 
 int SOCK_STREAM ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int fork () ; 
 int socketpair (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  zygote_main (int) ; 
 int zygote_sock ; 

int
zygote_init(void)
{
	int serrno, sp[2];
	pid_t pid;

	if (socketpair(PF_UNIX, SOCK_STREAM | SOCK_NONBLOCK, 0, sp) == -1)
		return (-1);

	pid = fork();
	switch (pid) {
	case -1:
		/* Failure. */
		serrno = errno;
		close(sp[0]);
		close(sp[1]);
		errno = serrno;
		return (-1);
	case 0:
		/* Child. */
		close(sp[0]);
		zygote_main(sp[1]);
		/* NOTREACHED */
		abort();
	default:
		/* Parent. */
		zygote_sock = sp[0];
		close(sp[1]);
		return (0);
	}
	/* NOTREACHED */
}