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
 scalar_t__ ENOTTY ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int STDIN_FILENO ; 
 int /*<<< orphan*/  TIOCGDRAINWAIT ; 
 int /*<<< orphan*/  TIOCMGDTRWAIT ; 
 int /*<<< orphan*/  TIOCMSDTRWAIT ; 
 int /*<<< orphan*/  TIOCSDRAINWAIT ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  isdigit (char) ; 
 int open (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warn (char*,...) ; 

int
main(int argc, char *argv[])
{
	int	fd;
	int     res = 0;
	int     print_dtrwait = 1, print_drainwait = 1;
	int     dtrwait = -1, drainwait = -1;

	if (argc < 2)
		usage();

	if (strcmp(argv[1], "-") == 0)
		fd = STDIN_FILENO;
	else {
		fd = open(argv[1], O_RDONLY|O_NONBLOCK, 0);
		if (fd < 0) {
			warn("couldn't open file %s", argv[1]);
			return 1;
		}
	}
	if (argc == 2) {
		if (ioctl(fd, TIOCMGDTRWAIT, &dtrwait) < 0) {
			print_dtrwait = 0;
			if (errno != ENOTTY) {
				res = 1;
				warn("TIOCMGDTRWAIT");
			}
		}
		if (ioctl(fd, TIOCGDRAINWAIT, &drainwait) < 0) {
			print_drainwait = 0;
			if (errno != ENOTTY) {
				res = 1;
				warn("TIOCGDRAINWAIT");
			}
		}
		if (print_dtrwait)
			printf("dtrwait %d ", dtrwait);
		if (print_drainwait)
			printf("drainwait %d ", drainwait);
		printf("\n");
	} else {
		while (argv[2] != NULL) {
			if (!strcmp(argv[2],"dtrwait")) {
				if (dtrwait >= 0)
					usage();
				if (argv[3] == NULL || !isdigit(argv[3][0]))
					usage();
				dtrwait = atoi(argv[3]);
				argv += 2;
			} else if (!strcmp(argv[2],"drainwait")) {
				if (drainwait >= 0)
					usage();
				if (argv[3] == NULL || !isdigit(argv[3][0]))
					usage();
				drainwait = atoi(argv[3]);
				argv += 2;
			} else
				usage();
		}
		if (dtrwait >= 0) {
			if (ioctl(fd, TIOCMSDTRWAIT, &dtrwait) < 0) {
				res = 1;
				warn("TIOCMSDTRWAIT");
			}
		}
		if (drainwait >= 0) {
			if (ioctl(fd, TIOCSDRAINWAIT, &drainwait) < 0) {
				res = 1;
				warn("TIOCSDRAINWAIT");
			}
		}
	}

	close(fd);
	return res;
}