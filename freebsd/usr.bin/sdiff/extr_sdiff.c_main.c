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
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  DIFFPROG_OPT 133 
 scalar_t__ EOF ; 
#define  FCASE_IGNORE_OPT 132 
#define  FCASE_SENSITIVE_OPT 131 
#define  HELP_OPT 130 
 int /*<<< orphan*/  INT_MAX ; 
 int Iflag ; 
 int SIZE_MAX ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
#define  STRIPCR_OPT 129 
#define  TSIZE_OPT 128 
 int WEXITSTATUS (int) ; 
 size_t WIDTH ; 
 int /*<<< orphan*/  WIDTH_MIN ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 char* _PATH_TMP ; 
 scalar_t__ asprintf (char**,char*) ; 
 int /*<<< orphan*/  binexec (char*,char*,char*) ; 
 char** calloc (int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 char* diff_path ; 
 int dup2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enqueue (char*,char,char*) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  execvp (char*,char**) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int file1ln ; 
 int file2ln ; 
 void* fopen (char const*,char*) ; 
 int /*<<< orphan*/  fork () ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char** help_msg ; 
 int /*<<< orphan*/  istextfile (int /*<<< orphan*/ *) ; 
 int lflag ; 
 int line_width ; 
 int /*<<< orphan*/  longopts ; 
 char* mktmpcpy (char*) ; 
 void* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/ * outfp ; 
 scalar_t__ parsecmd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pipe (int*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  processq () ; 
 char* realloc (char*,int) ; 
 int sflag ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 size_t strtonum (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 
 char* tmpdir ; 
 scalar_t__ unlink (char*) ; 
 int /*<<< orphan*/  usage () ; 
 int waitpid (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 
 int width ; 
 char* xfgets (int /*<<< orphan*/ *) ; 

int
main(int argc, char **argv)
{
	FILE *diffpipe=NULL, *file1, *file2;
	size_t diffargc = 0, wflag = WIDTH;
	int ch, fd[2] = {-1}, status;
	pid_t pid=0;
	const char *outfile = NULL;
	char **diffargv, *diffprog = diff_path, *filename1, *filename2,
	     *tmp1, *tmp2, *s1, *s2;
	int i;
	char I_arg[] = "-I";
	char speed_lf[] = "--speed-large-files";

	/*
	 * Process diff flags.
	 */
	/*
	 * Allocate memory for diff arguments and NULL.
	 * Each flag has at most one argument, so doubling argc gives an
	 * upper limit of how many diff args can be passed.  argv[0],
	 * file1, and file2 won't have arguments so doubling them will
	 * waste some memory; however we need an extra space for the
	 * NULL at the end, so it sort of works out.
	 */
	if (!(diffargv = calloc(argc, sizeof(char **) * 2)))
		err(2, "main");

	/* Add first argument, the program name. */
	diffargv[diffargc++] = diffprog;

	/* create a dynamic string for merging single-switch options */
	if ( asprintf(&diffargv[diffargc++], "-")  < 0 )
		err(2, "main");

	while ((ch = getopt_long(argc, argv, "aBbdEHI:ilo:stWw:",
	    longopts, NULL)) != -1) {
		const char *errstr;

		switch (ch) {
		/* only compatible --long-name-form with diff */
		case FCASE_IGNORE_OPT:
		case FCASE_SENSITIVE_OPT:
		case STRIPCR_OPT:
		case TSIZE_OPT:
		case 'S':
		break;
		/* combine no-arg single switches */
		case 'a':
		case 'B':
		case 'b':
		case 'd':
		case 'E':
		case 'i':
		case 't':
		case 'W':
			diffargv[1]  = realloc(diffargv[1], sizeof(char) * strlen(diffargv[1]) + 2);
			/*
			 * In diff, the 'W' option is 'w' and the 'w' is 'W'.
			 */
			if (ch == 'W')
				sprintf(diffargv[1], "%sw", diffargv[1]);
			else
				sprintf(diffargv[1], "%s%c", diffargv[1], ch);
			break;
		case 'H':
			diffargv[diffargc++] = speed_lf;
			break;
		case DIFFPROG_OPT:
			diffargv[0] = diffprog = optarg;
			break;
		case 'I':
			Iflag = 1;
			diffargv[diffargc++] = I_arg;
			diffargv[diffargc++] = optarg;
			break;
		case 'l':
			lflag = 1;
			break;
		case 'o':
			outfile = optarg;
			break;
		case 's':
			sflag = 1;
			break;
		case 'w':
			wflag = strtonum(optarg, WIDTH_MIN,
			    INT_MAX, &errstr);
			if (errstr)
				errx(2, "width is %s: %s", errstr, optarg);
			break;
		case HELP_OPT:
			for (i = 0; help_msg[i] != NULL; i++)
				printf("%s\n", help_msg[i]);
			exit(0);
			break;
		default:
			usage();
			break;
		}
	}

	/* no single switches were used */
	if (strcmp(diffargv[1], "-") == 0 ) {
		for ( i = 1; i < argc-1; i++) {
			diffargv[i] = diffargv[i+1];
		}
		diffargv[diffargc-1] = NULL;
		diffargc--;
	}

	argc -= optind;
	argv += optind;

	if (argc != 2)
		usage();

	if (outfile && (outfp = fopen(outfile, "w")) == NULL)
		err(2, "could not open: %s", optarg);

	if ((tmpdir = getenv("TMPDIR")) == NULL || *tmpdir == '\0')
		tmpdir = _PATH_TMP;

	filename1 = argv[0];
	filename2 = argv[1];

	/*
	 * Create temporary files for diff and sdiff to share if file1
	 * or file2 are not regular files.  This allows sdiff and diff
	 * to read the same inputs if one or both inputs are stdin.
	 *
	 * If any temporary files were created, their names would be
	 * saved in tmp1 or tmp2.  tmp1 should never equal tmp2.
	 */
	tmp1 = tmp2 = NULL;
	/* file1 and file2 are the same, so copy to same temp file. */
	if (strcmp(filename1, filename2) == 0) {
		if ((tmp1 = mktmpcpy(filename1)))
			filename1 = filename2 = tmp1;
	/* Copy file1 and file2 into separate temp files. */
	} else {
		if ((tmp1 = mktmpcpy(filename1)))
			filename1 = tmp1;
		if ((tmp2 = mktmpcpy(filename2)))
			filename2 = tmp2;
	}

	diffargv[diffargc++] = filename1;
	diffargv[diffargc++] = filename2;
	/* Add NULL to end of array to indicate end of array. */
	diffargv[diffargc++] = NULL;

	/* Subtract column divider and divide by two. */
	width = (wflag - 3) / 2;
	/* Make sure line_width can fit in size_t. */
	if (width > (SIZE_MAX - 3) / 2)
		errx(2, "width is too large: %zu", width);
	line_width = width * 2 + 3;

	if (pipe(fd))
		err(2, "pipe");

	switch (pid = fork()) {
	case 0:
		/* child */
		/* We don't read from the pipe. */
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			err(2, "child could not duplicate descriptor");
		/* Free unused descriptor. */
		close(fd[1]);
		execvp(diffprog, diffargv);
		err(2, "could not execute diff: %s", diffprog);
		break;
	case -1:
		err(2, "could not fork");
		break;
	}

	/* parent */
	/* We don't write to the pipe. */
	close(fd[1]);

	/* Open pipe to diff command. */
	if ((diffpipe = fdopen(fd[0], "r")) == NULL)
		err(2, "could not open diff pipe");

	if ((file1 = fopen(filename1, "r")) == NULL)
		err(2, "could not open %s", filename1);
	if ((file2 = fopen(filename2, "r")) == NULL)
		err(2, "could not open %s", filename2);
	if (!istextfile(file1) || !istextfile(file2)) {
		/* Close open files and pipe, delete temps */
		fclose(file1);
		fclose(file2);
		if (diffpipe != NULL)
			fclose(diffpipe);
		if (tmp1)
			if (unlink(tmp1))
				warn("Error deleting %s.", tmp1);
		if (tmp2)
			if (unlink(tmp2))
				warn("Error deleting %s.", tmp2);
		free(tmp1);
		free(tmp2);
		binexec(diffprog, filename1, filename2);
	}
	/* Line numbers start at one. */
	file1ln = file2ln = 1;

	/* Read and parse diff output. */
	while (parsecmd(diffpipe, file1, file2) != EOF)
		;
	fclose(diffpipe);

	/* Wait for diff to exit. */
	if (waitpid(pid, &status, 0) == -1 || !WIFEXITED(status) ||
	    WEXITSTATUS(status) >= 2)
		err(2, "diff exited abnormally.");

	/* Delete and free unneeded temporary files. */
	if (tmp1)
		if (unlink(tmp1))
			warn("Error deleting %s.", tmp1);
	if (tmp2)
		if (unlink(tmp2))
			warn("Error deleting %s.", tmp2);
	free(tmp1);
	free(tmp2);
	filename1 = filename2 = tmp1 = tmp2 = NULL;

	/* No more diffs, so print common lines. */
	if (lflag)
		while ((s1 = xfgets(file1)))
			enqueue(s1, ' ', NULL);
	else
		for (;;) {
			s1 = xfgets(file1);
			s2 = xfgets(file2);
			if (s1 || s2)
				enqueue(s1, ' ', s2);
			else
				break;
		}
	fclose(file1);
	fclose(file2);
	/* Process unmodified lines. */
	processq();

	/* Return diff exit status. */
	return (WEXITSTATUS(status));
}