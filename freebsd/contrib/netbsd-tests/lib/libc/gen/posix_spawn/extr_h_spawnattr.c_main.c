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
struct sigaction {void* sa_sigaction; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 scalar_t__ SIG_DFL ; 
 int atoi (char*) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* getprogname () ; 
 int /*<<< orphan*/  printf (char*,char*,int,...) ; 
 int read (int,char*,int) ; 
 scalar_t__ sigaction (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sigaction*) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigismember (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

int
main(int argc, char **argv)
{
	int parent_pipe, res = EXIT_SUCCESS;
	sigset_t sig;
	struct sigaction act;
	ssize_t rd;
	char tmp;

	sigemptyset(&sig);
	if (sigprocmask(0, NULL, &sig) < 0) {
		fprintf(stderr, "%s: sigprocmask error\n", getprogname());
		res = EXIT_FAILURE;
	}
	if (!sigismember(&sig, SIGUSR1)) {
		fprintf(stderr, "%s: SIGUSR not in procmask\n", getprogname());
		res = EXIT_FAILURE;
	}
	if (sigaction(SIGUSR1, NULL, &act) < 0) {
		fprintf(stderr, "%s: sigaction error\n", getprogname());
		res = EXIT_FAILURE;
	}
	if (act.sa_sigaction != (void *)SIG_DFL) {
		fprintf(stderr, "%s: SIGUSR1 action != SIG_DFL\n",
		    getprogname());
		res = EXIT_FAILURE;
	}

	if (argc >= 2) {
		parent_pipe = atoi(argv[1]);
		if (parent_pipe > 2) {
			printf("%s: waiting for command from parent on pipe "
			    "%d\n", getprogname(), parent_pipe);
			rd = read(parent_pipe, &tmp, 1);
			if (rd == 1) {
				printf("%s: got command %c from parent\n",
				    getprogname(), tmp);
			} else if (rd == -1) {
				printf("%s: %d is no pipe, errno %d\n",
				    getprogname(), parent_pipe, errno);
				res = EXIT_FAILURE;
			}
		}
	}

	return res;
}