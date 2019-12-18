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
typedef  int /*<<< orphan*/  av ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 char** calloc (int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  execvp (char*,char**) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  stderr ; 
 char* strdup (char const* const) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
exec_command(int argc, const char *const argv[])
{
	pid_t child_pid;
	pid_t wret;
	int child_status;
	int i;

	printf("Executing command: ");
	for (i = 0; i < argc - 1; i++) {
		if (!argv[i]) {
			/* Invalid argument. */
			return -1;
		}
		if (i > 0) {
			putchar(' ');
		}
		printf("%s", argv[i]);
	}
	putchar('\n');

	child_pid = fork();
	if (child_pid == 0) {
		char **av;
		int fds[3];

		/* Child process. Redirect stdin, stdout
		 * and stderr. */
		for (i = 0; i < 3; i++) {
			close(i);
			fds[i] = open("/dev/null", O_RDONLY);
			if (fds[i] < 0) {
				for (i--; i >= 0; i--) {
					close(fds[i]);
				}
				return -1;
			}
		}

		/* Make a copy of the arguments, passing them to execvp. */
		av = calloc(argc, sizeof(av[0]));
		if (!av) {
			exit(EXIT_FAILURE);
		}
		for (i = 0; i < argc - 1; i++) {
			av[i] = strdup(argv[i]);
			if (!av[i]) {
				exit(EXIT_FAILURE);
			}
		}
		execvp(av[0], av);
		perror("execvp()");
		exit(EXIT_FAILURE);
	}

	wret = waitpid(child_pid, &child_status, 0);
	if (wret < 0) {
		fprintf(stderr, "waitpid() failed: %s\n", strerror(errno));
		return wret;
	}
	if (WIFEXITED(child_status)) {
		return WEXITSTATUS(child_status);
	}

	return -1;
}