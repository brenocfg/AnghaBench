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
 scalar_t__ EMFILE ; 
 scalar_t__ ENFILE ; 
 int /*<<< orphan*/  PF_UNIX ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  close2 (int,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,int,int) ; 
 int getdeferred () ; 
 int /*<<< orphan*/  my_socketpair (int*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  save_sysctls (int*,int*) ; 
 int /*<<< orphan*/  sendfd (int,int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 char* test ; 
 int /*<<< orphan*/  test_sysctls (int,int) ; 

__attribute__((used)) static void
recursion(void)
{
	int fd[2], ff[2];
	int inflight, openfiles, deferred, deferred1;

	test = "recursion";
	printf("%s\n", test);
	save_sysctls(&inflight, &openfiles);
	deferred = getdeferred();

	my_socketpair(fd);

	for (;;) {
		if (socketpair(PF_UNIX, SOCK_STREAM, 0, ff) == -1) {
			if (errno == EMFILE || errno == ENFILE)
				break;
			err(-1, "socketpair");
		}
		sendfd(ff[0], fd[0]);
		sendfd(ff[0], fd[1]);
		close2(fd[1], fd[0]);
		fd[0] = ff[0];
		fd[1] = ff[1];
	}
	close2(fd[0], fd[1]);
	sleep(1);
	test_sysctls(inflight, openfiles);
	deferred1 = getdeferred();
	if (deferred != deferred1)
		errx(-1, "recursion: deferred before %d after %d", deferred,
		    deferred1);
}