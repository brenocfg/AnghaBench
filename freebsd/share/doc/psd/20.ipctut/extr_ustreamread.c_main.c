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
struct sockaddr_un {char* sun_path; int /*<<< orphan*/  sun_family; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  NAME ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int accept (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bind (int,struct sockaddr_un*,int) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  listen (int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read (int,char*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

main()
{
	int sock, msgsock, rval;
	struct sockaddr_un server;
	char buf[1024];

	/* Create socket */
	sock = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("opening stream socket");
		exit(1);
	}
	/* Name socket using file system name */
	server.sun_family = AF_UNIX;
	strcpy(server.sun_path, NAME);
	if (bind(sock, &server, sizeof(struct sockaddr_un))) {
		perror("binding stream socket");
		exit(1);
	}
	printf("Socket has name %s\en", server.sun_path);
	/* Start accepting connections */
	listen(sock, 5);
	for (;;) {
		msgsock = accept(sock, 0, 0);
		if (msgsock == -1)
			perror("accept");
		else do {
			bzero(buf, sizeof(buf));
			if ((rval = read(msgsock, buf, 1024)) < 0)
				perror("reading stream message");
			else if (rval == 0)
				printf("Ending connection\en");
			else
				printf("-->%s\en", buf);
		} while (rval > 0);
		close(msgsock);
	}
	/*
	 * The following statements are not executed, because they follow an
	 * infinite loop.  However, most ordinary programs will not run
	 * forever.  In the UNIX domain it is necessary to tell the file
	 * system that one is through using NAME.  In most programs one uses
	 * the call unlink() as below. Since the user will have to kill this
	 * program, it will be necessary to remove the name by a command from
	 * the shell.
	 */
	close(sock);
	unlink(NAME);
}