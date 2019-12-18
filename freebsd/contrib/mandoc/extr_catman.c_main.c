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
 int /*<<< orphan*/  AF_LOCAL ; 
 int /*<<< orphan*/  AF_UNSPEC ; 
 int O_DIRECTORY ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int chdir (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int fork () ; 
 int getopt (int,char**,char*) ; 
 int open (char*,int) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int process_tree (int,int) ; 
 int /*<<< orphan*/  run_mandocd (int,char const*,char const*) ; 
 int socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char **argv)
{
	const char	*defos, *outtype;
	int		 srv_fds[2];
	int		 dstdir_fd;
	int		 opt;
	pid_t		 pid;

	defos = NULL;
	outtype = "ascii";
	while ((opt = getopt(argc, argv, "I:T:")) != -1) {
		switch (opt) {
		case 'I':
			defos = optarg;
			break;
		case 'T':
			outtype = optarg;
			break;
		default:
			usage();
		}
	}

	if (argc > 0) {
		argc -= optind;
		argv += optind;
	}
	if (argc != 2)
		usage();

	if (socketpair(AF_LOCAL, SOCK_STREAM, AF_UNSPEC, srv_fds) == -1)
		err(1, "socketpair");

	pid = fork();
	switch (pid) {
	case -1:
		err(1, "fork");
	case 0:
		close(srv_fds[0]);
		run_mandocd(srv_fds[1], outtype, defos);
	default:
		break;
	}
	close(srv_fds[1]);

	if ((dstdir_fd = open(argv[1], O_RDONLY | O_DIRECTORY)) == -1)
		err(1, "open(%s)", argv[1]);

	if (chdir(argv[0]) == -1)
		err(1, "chdir(%s)", argv[0]);

	return process_tree(srv_fds[0], dstdir_fd) == -1 ? 1 : 0;
}