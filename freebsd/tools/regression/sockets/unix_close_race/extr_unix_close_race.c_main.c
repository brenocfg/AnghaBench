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
typedef  int u_int ;
struct sockaddr_un {int /*<<< orphan*/  sun_path; void* sun_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  servaddr ;
typedef  int /*<<< orphan*/  ncpus ;

/* Variables and functions */
 void* AF_LOCAL ; 
 int LOOPS ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  USLEEP ; 
 int accept (int,struct sockaddr*,int /*<<< orphan*/ *) ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_un*,int) ; 
 scalar_t__ close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int fork () ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 
 scalar_t__ listen (int,int) ; 
 int mkstemp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int socket (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_path ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sysctlbyname (char*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
main(void)
{
	struct sockaddr_un servaddr;
	int listenfd, connfd, pid;
	u_int counter, ncpus;
	size_t len;

	len = sizeof(ncpus);
	if (sysctlbyname("kern.smp.cpus", &ncpus, &len, NULL, 0) < 0)
		err(1, "kern.smp.cpus");
	if (len != sizeof(ncpus))
		errx(1, "kern.smp.cpus: invalid length");
	if (ncpus < 2)
		warnx("SMP not present, test may be unable to trigger race");

	if (mkstemp(socket_path) == -1)
		err(1, "mkstemp failed");
	unlink(socket_path);

	/*
	 * Create a UNIX domain socket that the child will repeatedly
	 * accept() from, and that the parent will repeatedly connect() to.
	 */
	if ((listenfd = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0)
		err(1, "parent: socket error");
	(void)unlink(socket_path);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_LOCAL;
	strcpy(servaddr.sun_path, socket_path);
	if (bind(listenfd, (struct sockaddr *) &servaddr,
	    sizeof(servaddr)) < 0)
		err(1, "parent: bind error");
	if (listen(listenfd, 1024) < 0)
		err(1, "parent: listen error");

	pid = fork();
	if (pid == -1)
		err(1, "fork()");
	if (pid != 0) {
		/*
		 * In the parent, repeatedly connect and disconnect from the
		 * socket, attempting to induce the race.
		 */
		close(listenfd);
		sleep(1);
		bzero(&servaddr, sizeof(servaddr));
		servaddr.sun_family = AF_LOCAL;
		strcpy(servaddr.sun_path, socket_path);
		for (counter = 0; counter < LOOPS; counter++) {
			if ((connfd = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0) {
				(void)kill(pid, SIGTERM);
				err(1, "parent: socket error");
			}
			if (connect(connfd, (struct sockaddr *)&servaddr,
			    sizeof(servaddr)) < 0) {
			    	(void)kill(pid, SIGTERM);
				err(1, "parent: connect error");
			}
			if (close(connfd) < 0) {
				(void)kill(pid, SIGTERM);
				err(1, "parent: close error");
			}
			usleep(USLEEP);
		}
		(void)kill(pid, SIGTERM);
	} else {
		/*
		 * In the child, loop accepting and closing.  We may pick up
		 * the race here so report errors from close().
		 */
		for ( ; ; ) {
			if ((connfd = accept(listenfd,
			    (struct sockaddr *)NULL, NULL)) < 0)
				err(1, "child: accept error");
			if (close(connfd) < 0)
				err(1, "child: close error");
		}
	}
	printf("OK\n");
	exit(0);
}