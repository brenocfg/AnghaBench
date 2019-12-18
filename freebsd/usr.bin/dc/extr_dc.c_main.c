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
 int /*<<< orphan*/  CAPH_READ ; 
 char* DC_VER ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  _IOLBF ; 
 char* __progname ; 
 scalar_t__ caph_enter () ; 
 scalar_t__ caph_limit_stdio () ; 
 scalar_t__ caph_limit_stream (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  eval () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_bmachine (int) ; 
 int /*<<< orphan*/  long_options ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  procfd (int,char*) ; 
 int /*<<< orphan*/  reset_bmachine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  src ; 
 int /*<<< orphan*/  src_setstream (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  src_setstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	int ch, fd;
	bool extended_regs = false, preproc_done = false;

	/* accept and ignore a single dash to be 4.4BSD dc(1) compatible */
	while ((ch = getopt_long(argc, argv, "e:f:hVx", long_options, NULL)) != -1) {
		switch (ch) {
		case 'e':
			if (!preproc_done)
				init_bmachine(extended_regs);
			src_setstring(&src, optarg);
			reset_bmachine(&src);
			eval();
			preproc_done = true;
			break;
		case 'f':
			if (!preproc_done)
				init_bmachine(extended_regs);
			fd = open(optarg, O_RDONLY);
			if (fd < 0)
				err(1, "cannot open file %s", optarg);
			procfd(fd, optarg);
			preproc_done = true;
			break;
		case 'x':
			extended_regs = true;
			break;
		case 'V':
			fprintf(stderr, "%s (BSD bc) %s\n", __progname, DC_VER);
			exit(0);
			break;
		case '-':
			break;
		case 'h':
			/* FALLTHROUGH */
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (!preproc_done)
		init_bmachine(extended_regs);
	(void)setvbuf(stdout, NULL, _IOLBF, 0);
	(void)setvbuf(stderr, NULL, _IOLBF, 0);

	if (argc > 1)
		usage();
	if (argc == 1) {
		fd = open(argv[0], O_RDONLY);
		if (fd < 0)
			err(1, "cannot open file %s", argv[0]);

		if (caph_limit_stream(fd, CAPH_READ) < 0 ||
		    caph_limit_stdio() < 0 ||
		    caph_enter() < 0)
			err(1, "capsicum");

		procfd(fd, argv[0]);
		preproc_done = true;
	}
	if (preproc_done)
		return (0);

	if (caph_limit_stdio() < 0 || caph_enter())
		err(1, "capsicum");
	src_setstream(&src, stdin);
	reset_bmachine(&src);
	eval();

	return (0);
}