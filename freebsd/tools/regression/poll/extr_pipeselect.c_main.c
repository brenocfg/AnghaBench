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
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  FIFONAME ; 
 int FT_END ; 
#define  FT_FIFO 130 
#define  FT_PIPE 129 
#define  FT_SOCKETPAIR 128 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  catch ; 
 int /*<<< orphan*/  child (int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  cpid ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int filetype ; 
 int /*<<< orphan*/  fork () ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  mkfifo (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parent (int) ; 
 int /*<<< orphan*/  pipe (int*) ; 
 int /*<<< orphan*/  ppid ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ state ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

int
main(void)
{
	int fd[2], num;

	num = 1;
	printf("1..20\n");
	fflush(stdout);
	signal(SIGUSR1, catch);
	ppid = getpid();
	for (filetype = 0; filetype < FT_END; filetype++) {
		switch (filetype) {
		case FT_FIFO:
			if (mkfifo(FIFONAME, 0666) != 0)
				err(1, "mkfifo");
			fd[0] = -1;
			fd[1] = -1;
			break;
		case FT_SOCKETPAIR:
			if (socketpair(AF_UNIX, SOCK_STREAM, AF_UNSPEC,
			    fd) != 0)
				err(1, "socketpair");
			break;
		case FT_PIPE:
			if (pipe(fd) != 0)
				err(1, "pipe");
			break;
		}
		state = 0;
		switch (cpid = fork()) {
		case -1:
			err(1, "fork");
		case 0:
			(void)close(fd[1]);
			child(fd[0], num);
			break;
		default:
			(void)close(fd[0]);
			parent(fd[1]);
			break;
		}
		num += filetype == FT_FIFO ? 12 : 4;
	}
	(void)unlink(FIFONAME);
	return (0);
}