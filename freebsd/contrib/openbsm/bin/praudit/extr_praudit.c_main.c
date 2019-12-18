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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int AU_OFLAG_NORESOLVE ; 
 int AU_OFLAG_RAW ; 
 int AU_OFLAG_SHORT ; 
 int AU_OFLAG_XML ; 
 scalar_t__ ENOSYS ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  au_print_xml_footer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au_print_xml_header (int /*<<< orphan*/ ) ; 
 int cap_enter () ; 
 int /*<<< orphan*/  del ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  getauevent () ; 
 int /*<<< orphan*/  getgrgid (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  getpwuid (int /*<<< orphan*/ ) ; 
 int oflags ; 
 int oneline ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 int partial ; 
 int /*<<< orphan*/  perror (char*) ; 
 int print_tokens (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setgroupent (int) ; 
 int /*<<< orphan*/  setpassent (int) ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  usage () ; 
 scalar_t__ waitpid (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
main(int argc, char **argv)
{
	int ch;
	int i;
#ifdef HAVE_CAP_ENTER
	int retval;
	pid_t childpid, pid;
#endif
	FILE *fp;

	while ((ch = getopt(argc, argv, "d:lnprsx")) != -1) {
		switch(ch) {
		case 'd':
			del = optarg;
			break;

		case 'l':
			oneline = 1;
			break;

		case 'n':
			oflags |= AU_OFLAG_NORESOLVE;
			break;

		case 'p':
			partial = 1;
			break;

		case 'r':
			if (oflags & AU_OFLAG_SHORT)
				usage();	/* Exclusive from shortfrm. */
			oflags |= AU_OFLAG_RAW;
			break;

		case 's':
			if (oflags & AU_OFLAG_RAW)
				usage();	/* Exclusive from raw. */
			oflags |= AU_OFLAG_SHORT;
			break;

		case 'x':
			oflags |= AU_OFLAG_XML;
			break;

		case '?':
		default:
			usage();
		}
	}

#ifdef HAVE_CAP_ENTER
	/*
	 * Prime group, password, and audit-event files to be opened before we
	 * enter capability mode.
	 */
	(void)getgrgid(0);
	(void)setgroupent(1);
	(void)getpwuid(0);
	(void)setpassent(1);
	(void)getauevent();
#endif

	if (oflags & AU_OFLAG_XML)
		au_print_xml_header(stdout);

	/* For each of the files passed as arguments dump the contents. */
	if (optind == argc) {
#ifdef HAVE_CAP_ENTER
		retval = cap_enter();
		if (retval != 0 && errno != ENOSYS)
			err(EXIT_FAILURE, "cap_enter");
#endif
		print_tokens(stdin);
		return (1);
	}
	for (i = optind; i < argc; i++) {
		fp = fopen(argv[i], "r");
		if (fp == NULL) {
			perror(argv[i]);
			continue;
		}

		/*
		 * If operating with sandboxing, create a sandbox process for
		 * each trail file we operate on.  This avoids the need to do
		 * fancy things with file descriptors, etc, when iterating on
		 * a list of arguments.
		 */
#ifdef HAVE_CAP_ENTER
		childpid = fork();
		if (childpid == 0) {
			/* Child. */
			retval = cap_enter();
			if (retval != 0 && errno != ENOSYS)
				err(EXIT_FAILURE, "cap_enter");
			if (print_tokens(fp) == -1)
				perror(argv[i]);
			exit(0);
		}

		/* Parent.  Await child termination. */
		while ((pid = waitpid(childpid, NULL, 0)) != childpid);
#else
		if (print_tokens(fp) == -1)
			perror(argv[i]);
#endif
		fclose(fp);
	}

	if (oflags & AU_OFLAG_XML)
		au_print_xml_footer(stdout);

	return (0);
}