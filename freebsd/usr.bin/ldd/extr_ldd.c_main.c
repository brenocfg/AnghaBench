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
 int EDOOFUS ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  LDD_SETENV (char*,char*,int) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  RTLD_TRACE ; 
#define  TYPE_AOUT 131 
#define  TYPE_ELF 130 
#define  TYPE_ELF32 129 
#define  TYPE_UNKNOWN 128 
 int WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int /*<<< orphan*/  WIFSIGNALED (int) ; 
 int WTERMSIG (int) ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dlerror () ; 
 int /*<<< orphan*/  dlopen (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_file (char*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ error_count ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  execl (char*,char*,char*) ; 
 int execldd32 (char*,char*,char*,int,int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int) ; 
 int getopt (int,char**,char*) ; 
 int is_executable (char*,int,int*,int*) ; 
 int open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  wait (int*) ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  warnx (char*,char*,int /*<<< orphan*/ ) ; 

int
main(int argc, char *argv[])
{
	char *fmt1, *fmt2;
	int rval, c, aflag, vflag;

	aflag = vflag = 0;
	fmt1 = fmt2 = NULL;

	while ((c = getopt(argc, argv, "af:v")) != -1) {
		switch (c) {
		case 'a':
			aflag++;
			break;
		case 'f':
			if (fmt1 != NULL) {
				if (fmt2 != NULL)
					errx(1, "too many formats");
				fmt2 = optarg;
			} else
				fmt1 = optarg;
			break;
		case 'v':
			vflag++;
			break;
		default:
			usage();
			/* NOTREACHED */
		}
	}
	argc -= optind;
	argv += optind;

	if (vflag && fmt1 != NULL)
		errx(1, "-v may not be used with -f");

	if (argc <= 0) {
		usage();
		/* NOTREACHED */
	}

#ifdef __i386__
	if (vflag) {
		for (c = 0; c < argc; c++)
			dump_file(argv[c]);
		exit(error_count == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
	}
#endif

	rval = 0;
	for (; argc > 0; argc--, argv++) {
		int fd, status, is_shlib, rv, type;

		if ((fd = open(*argv, O_RDONLY, 0)) < 0) {
			warn("%s", *argv);
			rval |= 1;
			continue;
		}
		rv = is_executable(*argv, fd, &is_shlib, &type);
		close(fd);
		if (rv == 0) {
			rval |= 1;
			continue;
		}

		switch (type) {
		case TYPE_ELF:
		case TYPE_AOUT:
			break;
#if __ELF_WORD_SIZE > 32 && defined(ELF32_SUPPORTED)
		case TYPE_ELF32:
			rval |= execldd32(*argv, fmt1, fmt2, aflag, vflag);
			continue;
#endif
		case TYPE_UNKNOWN:
		default:
			/*
			 * This shouldn't happen unless is_executable()
			 * is broken.
			 */
			errx(EDOOFUS, "unknown executable type");
		}

		/* ld.so magic */
		LDD_SETENV("TRACE_LOADED_OBJECTS", "yes", 1);
		if (fmt1 != NULL)
			LDD_SETENV("TRACE_LOADED_OBJECTS_FMT1", fmt1, 1);
		if (fmt2 != NULL)
			LDD_SETENV("TRACE_LOADED_OBJECTS_FMT2", fmt2, 1);

		LDD_SETENV("TRACE_LOADED_OBJECTS_PROGNAME", *argv, 1);
		if (aflag)
			LDD_SETENV("TRACE_LOADED_OBJECTS_ALL", "1", 1);
		else if (fmt1 == NULL && fmt2 == NULL)
			/* Default formats */
			printf("%s:\n", *argv);
		fflush(stdout);

		switch (fork()) {
		case -1:
			err(1, "fork");
			break;
		default:
			if (wait(&status) < 0) {
				warn("wait");
				rval |= 1;
			} else if (WIFSIGNALED(status)) {
				fprintf(stderr, "%s: signal %d\n", *argv,
				    WTERMSIG(status));
				rval |= 1;
			} else if (WIFEXITED(status) &&
			    WEXITSTATUS(status) != 0) {
				fprintf(stderr, "%s: exit status %d\n", *argv,
				    WEXITSTATUS(status));
				rval |= 1;
			}
			break;
		case 0:
			if (is_shlib == 0) {
				execl(*argv, *argv, (char *)NULL);
				warn("%s", *argv);
			} else {
				dlopen(*argv, RTLD_TRACE);
				warnx("%s: %s", *argv, dlerror());
			}
			_exit(1);
		}
	}

	return rval;
}