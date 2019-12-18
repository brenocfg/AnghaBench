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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int STDIN_FILENO ; 
 int /*<<< orphan*/  close (int) ; 
 int crc (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int crc32 (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int csum1 (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int csum2 (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 int open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 void pcrc (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void psum1 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void psum2 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warn (char*,char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
main(int argc, char **argv)
{
	uint32_t val;
	int ch, fd, rval;
	off_t len;
	char *fn, *p;
	int (*cfncn)(int, uint32_t *, off_t *);
	void (*pfncn)(char *, uint32_t, off_t);

	if ((p = strrchr(argv[0], '/')) == NULL)
		p = argv[0];
	else
		++p;
	if (!strcmp(p, "sum")) {
		cfncn = csum1;
		pfncn = psum1;
		++argv;
	} else {
		cfncn = crc;
		pfncn = pcrc;

		while ((ch = getopt(argc, argv, "o:")) != -1)
			switch (ch) {
			case 'o':
				if (!strcmp(optarg, "1")) {
					cfncn = csum1;
					pfncn = psum1;
				} else if (!strcmp(optarg, "2")) {
					cfncn = csum2;
					pfncn = psum2;
				} else if (!strcmp(optarg, "3")) {
					cfncn = crc32;
					pfncn = pcrc;
				} else {
					warnx("illegal argument to -o option");
					usage();
				}
				break;
			case '?':
			default:
				usage();
			}
		argc -= optind;
		argv += optind;
	}

	fd = STDIN_FILENO;
	fn = NULL;
	rval = 0;
	do {
		if (*argv) {
			fn = *argv++;
			if ((fd = open(fn, O_RDONLY, 0)) < 0) {
				warn("%s", fn);
				rval = 1;
				continue;
			}
		}
		if (cfncn(fd, &val, &len)) {
			warn("%s", fn ? fn : "stdin");
			rval = 1;
		} else
			pfncn(fn, val, len);
		(void)close(fd);
	} while (*argv);
	exit(rval);
}