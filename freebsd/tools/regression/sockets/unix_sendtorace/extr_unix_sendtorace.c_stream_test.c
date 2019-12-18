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
typedef  int /*<<< orphan*/  sun ;
struct sockaddr_un {int sun_len; int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int dummy; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  PF_UNIX ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_un*,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  kill (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ listen (int,int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_path ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stream_client () ; 
 int /*<<< orphan*/  stream_server (int) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
stream_test(void)
{
	struct sockaddr_un sun;
	pid_t childpid;
	int listenfd;

	listenfd = socket(PF_UNIX, SOCK_STREAM, 0);
	if (listenfd < 0)
		err(-1, "stream_test: socket");

	bzero(&sun, sizeof(sun));
	sun.sun_len = sizeof(sun);
	sun.sun_family = AF_UNIX;
	strcpy(sun.sun_path, socket_path);

	if (bind(listenfd, (struct sockaddr *)&sun, sizeof(sun)) < 0)
		err(-1, "stream_test: bind");

	if (listen(listenfd, -1) < 0)
		err(-1, "stream_test: listen");

	childpid = fork();
	if (childpid < 0)
		err(-1, "stream_test: fork");

	if (childpid != 0) {
		sleep(1);
		stream_client();
		kill(childpid, SIGTERM);
		sleep(1);
	} else
		stream_server(listenfd);

	(void)unlink(socket_path);
}