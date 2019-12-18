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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 int EX_NOINPUT ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int SIZE_T_MAX ; 
 void* XMALLOC (scalar_t__) ; 
 int allow_indented_paragraphs ; 
 int centerP ; 
 int coalesce_spaces_P ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int format_troff ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_nonnegative (char*,char*,int) ; 
 void* get_positive (char*,char*,int) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ goal_length ; 
 int grok_mail_headers ; 
 scalar_t__ max_length ; 
 size_t mbsrtowcs (int /*<<< orphan*/ *,char const**,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ n_errors ; 
 char* optarg ; 
 size_t optind ; 
 void* output_buffer ; 
 int /*<<< orphan*/  output_tab_width ; 
 int /*<<< orphan*/  process_named_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_stream (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * sentence_enders ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 void* tab_width ; 

int
main(int argc, char *argv[])
{
	int ch;				/* used for |getopt| processing */
	wchar_t *tmp;
	size_t len;
	const char *src;

	(void)setlocale(LC_CTYPE, "");

	/* 1. Grok parameters. */

	while ((ch = getopt(argc, argv, "0123456789cd:hl:mnpst:w:")) != -1)
		switch (ch) {
		case 'c':
			centerP = 1;
			format_troff = 1;
			continue;
		case 'd':
			src = optarg;
			len = mbsrtowcs(NULL, &src, 0, NULL);
			if (len == (size_t)-1)
				err(EX_USAGE, "bad sentence-ending character set");
			tmp = XMALLOC((len + 1) * sizeof(wchar_t));
			mbsrtowcs(tmp, &src, len + 1, NULL);
			sentence_enders = tmp;
			continue;
		case 'l':
			output_tab_width
			    = get_nonnegative(optarg, "output tab width must be non-negative", 1);
			continue;
		case 'm':
			grok_mail_headers = 1;
			continue;
		case 'n':
			format_troff = 1;
			continue;
		case 'p':
			allow_indented_paragraphs = 1;
			continue;
		case 's':
			coalesce_spaces_P = 1;
			continue;
		case 't':
			tab_width = get_positive(optarg, "tab width must be positive", 1);
			continue;
		case 'w':
			goal_length = get_positive(optarg, "width must be positive", 1);
			max_length = goal_length;
			continue;
		case '0': case '1': case '2': case '3': case '4': case '5':
		case '6': case '7': case '8': case '9':
			/*
			 * XXX  this is not a stylistically approved use of
			 * getopt()
			 */
			if (goal_length == 0) {
				char *p;

				p = argv[optind - 1];
				if (p[0] == '-' && p[1] == ch && !p[2])
					goal_length = get_positive(++p, "width must be nonzero", 1);
				else
					goal_length = get_positive(argv[optind] + 1,
					    "width must be nonzero", 1);
				max_length = goal_length;
			}
			continue;
		case 'h':
		default:
			fprintf(stderr,
			    "usage:   fmt [-cmps] [-d chars] [-l num] [-t num]\n"
			    "             [-w width | -width | goal [maximum]] [file ...]\n"
			    "Options: -c     center each line instead of formatting\n"
			    "         -d <chars> double-space after <chars> at line end\n"
			    "         -l <n> turn each <n> spaces at start of line into a tab\n"
			    "         -m     try to make sure mail header lines stay separate\n"
			    "         -n     format lines beginning with a dot\n"
			    "         -p     allow indented paragraphs\n"
			    "         -s     coalesce whitespace inside lines\n"
			    "         -t <n> have tabs every <n> columns\n"
			    "         -w <n> set maximum width to <n>\n"
			    "         goal   set target width to goal\n");
			exit(ch == 'h' ? 0 : EX_USAGE);
		}
	argc -= optind;
	argv += optind;

	/* [ goal [ maximum ] ] */

	if (argc > 0 && goal_length == 0
	    && (goal_length = get_positive(*argv, "goal length must be positive", 0))
	    != 0) {
		--argc;
		++argv;
		if (argc > 0
		    && (max_length = get_positive(*argv, "max length must be positive", 0))
		    != 0) {
			--argc;
			++argv;
			if (max_length < goal_length)
				errx(EX_USAGE, "max length must be >= goal length");
		}
	}
	if (goal_length == 0)
		goal_length = 65;
	if (max_length == 0)
		max_length = goal_length + 10;
	if (max_length >= SIZE_T_MAX / sizeof(wchar_t))
		errx(EX_USAGE, "max length too large");
	/* really needn't be longer */
	output_buffer = XMALLOC((max_length + 1) * sizeof(wchar_t));

	/* 2. Process files. */

	if (argc > 0) {
		while (argc-- > 0)
			process_named_file(*argv++);
	} else {
		process_stream(stdin, "standard input");
	}

	/* We're done. */

	return n_errors ? EX_NOINPUT : 0;

}