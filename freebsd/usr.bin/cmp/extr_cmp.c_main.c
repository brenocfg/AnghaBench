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
struct stat {scalar_t__ st_size; int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int CAPH_IGNORE_EBADF ; 
 int CAPH_WRITE ; 
 int /*<<< orphan*/  DIFF_EXIT ; 
 scalar_t__ EMLINK ; 
 int /*<<< orphan*/  ERR_EXIT ; 
 int O_NOFOLLOW ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_link (char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_regular (int,char const*,int /*<<< orphan*/ ,scalar_t__,int,char const*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  c_special (int,char const*,int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caph_cache_catpages () ; 
 scalar_t__ caph_limit_stream (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int lflag ; 
 int /*<<< orphan*/  long_opts ; 
 int open (char const*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*,char const*,char const*) ; 
 int sflag ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 int xflag ; 
 int zflag ; 

int
main(int argc, char *argv[])
{
	struct stat sb1, sb2;
	off_t skip1, skip2;
	int ch, fd1, fd2, oflag, special;
	const char *file1, *file2;

	oflag = O_RDONLY;
	while ((ch = getopt_long(argc, argv, "+hlsxz", long_opts, NULL)) != -1)
		switch (ch) {
		case 'h':		/* Don't follow symlinks */
			oflag |= O_NOFOLLOW;
			break;
		case 'l':		/* print all differences */
			lflag = 1;
			break;
		case 's':		/* silent run */
			sflag = 1;
			zflag = 1;
			break;
		case 'x':		/* hex output */
			lflag = 1;
			xflag = 1;
			break;
		case 'z':		/* compare size first */
			zflag = 1;
			break;
		case '?':
		default:
			usage();
		}
	argv += optind;
	argc -= optind;

	if (lflag && sflag)
		errx(ERR_EXIT, "specifying -s with -l or -x is not permitted");

	if (argc < 2 || argc > 4)
		usage();

	/* Don't limit rights on stdin since it may be one of the inputs. */
	if (caph_limit_stream(STDOUT_FILENO, CAPH_WRITE | CAPH_IGNORE_EBADF))
		err(ERR_EXIT, "unable to limit rights on stdout");
	if (caph_limit_stream(STDERR_FILENO, CAPH_WRITE | CAPH_IGNORE_EBADF))
		err(ERR_EXIT, "unable to limit rights on stderr");

	/* Backward compatibility -- handle "-" meaning stdin. */
	special = 0;
	if (strcmp(file1 = argv[0], "-") == 0) {
		special = 1;
		fd1 = STDIN_FILENO;
		file1 = "stdin";
	} else if ((fd1 = open(file1, oflag, 0)) < 0 && errno != EMLINK) {
		if (!sflag)
			err(ERR_EXIT, "%s", file1);
		else
			exit(ERR_EXIT);
	}
	if (strcmp(file2 = argv[1], "-") == 0) {
		if (special)
			errx(ERR_EXIT,
				"standard input may only be specified once");
		special = 1;
		fd2 = STDIN_FILENO;
		file2 = "stdin";
	} else if ((fd2 = open(file2, oflag, 0)) < 0 && errno != EMLINK) {
		if (!sflag)
			err(ERR_EXIT, "%s", file2);
		else
			exit(ERR_EXIT);
	}

	skip1 = argc > 2 ? strtol(argv[2], NULL, 0) : 0;
	skip2 = argc == 4 ? strtol(argv[3], NULL, 0) : 0;

	if (fd1 == -1) {
		if (fd2 == -1) {
			c_link(file1, skip1, file2, skip2);
			exit(0);
		} else if (!sflag)
			errx(ERR_EXIT, "%s: Not a symbolic link", file2);
		else
			exit(ERR_EXIT);
	} else if (fd2 == -1) {
		if (!sflag)
			errx(ERR_EXIT, "%s: Not a symbolic link", file1);
		else
			exit(ERR_EXIT);
	}

	/* FD rights are limited in c_special() and c_regular(). */
	caph_cache_catpages();

	if (!special) {
		if (fstat(fd1, &sb1)) {
			if (!sflag)
				err(ERR_EXIT, "%s", file1);
			else
				exit(ERR_EXIT);
		}
		if (!S_ISREG(sb1.st_mode))
			special = 1;
		else {
			if (fstat(fd2, &sb2)) {
				if (!sflag)
					err(ERR_EXIT, "%s", file2);
				else
					exit(ERR_EXIT);
			}
			if (!S_ISREG(sb2.st_mode))
				special = 1;
		}
	}

	if (special)
		c_special(fd1, file1, skip1, fd2, file2, skip2);
	else {
		if (zflag && sb1.st_size != sb2.st_size) {
			if (!sflag)
				(void) printf("%s %s differ: size\n",
				    file1, file2);
			exit(DIFF_EXIT);
		}
		c_regular(fd1, file1, skip1, sb1.st_size,
		    fd2, file2, skip2, sb2.st_size);
	}
	exit(0);
}