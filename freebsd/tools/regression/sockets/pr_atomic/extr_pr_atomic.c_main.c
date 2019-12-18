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
typedef  int /*<<< orphan*/  un ;
struct sockaddr_un {int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int dummy; } ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  AF_LOCAL ; 
 int /*<<< orphan*/  PF_LOCAL ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alarm (int) ; 
 int bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int fork () ; 
 int /*<<< orphan*/  handle_sigalrm ; 
 int /*<<< orphan*/  memset (struct sockaddr_un*,int /*<<< orphan*/ ,int) ; 
 int mkstemp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  myjmpbuf ; 
 int recvfrom (int,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sendto (int,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_path ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

int
main(void)
{
	struct sockaddr_un un;
	pid_t pid;
	int s;

	if (mkstemp(socket_path) == -1)
		err(1, "mkstemp");
	s = socket(PF_LOCAL, SOCK_DGRAM, 0);
	if (s == -1)
		errx(-1, "socket");
	memset(&un, 0, sizeof(un));
	un.sun_family = AF_LOCAL;
	unlink(socket_path);
	strcpy(un.sun_path, socket_path);
	if (bind(s, (struct sockaddr *)&un, sizeof(un)) == -1)
		errx(-1, "bind");
	pid = fork();
	if (pid == -1)
		errx(-1, "fork");
	if (pid == 0) {
		int conn;
		char buf[] = "AAAAAAAAA";

		close(s);
		conn = socket(AF_LOCAL, SOCK_DGRAM, 0);
		if (conn == -1)
			errx(-1,"socket");
		if (sendto(conn, buf, sizeof(buf), 0, (struct sockaddr *)&un,
		    sizeof(un)) != sizeof(buf))
			errx(-1,"sendto");
		close(conn);
		_exit(0);
	}

	sleep(5);

	/* Make sure the data is there when we try to receive it. */
	if (recvfrom(s, (void *)-1, 1, 0, NULL, NULL) != -1)
		errx(-1,"recvfrom succeeded when failure expected");

	(void)signal(SIGALRM, handle_sigalrm);
	if (setjmp(myjmpbuf) == 0) {
		/*
	 	 * This recvfrom will panic an unpatched system, and block
		 * a patched one.
		 */
		alarm(5);
		(void)recvfrom(s, (void *)-1, 1, 0, NULL, NULL);
	}

	/* We should reach here via longjmp() and all should be well. */

	return (0);
}