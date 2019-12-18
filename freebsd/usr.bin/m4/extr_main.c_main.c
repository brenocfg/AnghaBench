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
typedef  int /*<<< orphan*/  stae ;

/* Variables and functions */
 char EOS ; 
 int /*<<< orphan*/  FORMATTYPE ; 
 int /*<<< orphan*/  INITSTACKMAX ; 
 int /*<<< orphan*/  MAXOUT ; 
 int /*<<< orphan*/  SIGINT ; 
 scalar_t__ SIG_IGN ; 
 int /*<<< orphan*/  STACKMAX ; 
 scalar_t__ active ; 
 int /*<<< orphan*/  addtoincludepath (char*) ; 
 int /*<<< orphan*/ * bbase ; 
 int /*<<< orphan*/  bp ; 
 int /*<<< orphan*/  buf ; 
 int /*<<< orphan*/  bufbase ; 
 int /*<<< orphan*/  dodefine (char*,char*) ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int error_warns ; 
 int exit_code ; 
 int fatal_warns ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen_trypath (scalar_t__,char*) ; 
 scalar_t__ fp ; 
 int /*<<< orphan*/  getdiv (int) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ ilevel ; 
 scalar_t__ infile ; 
 int /*<<< orphan*/  init_macros () ; 
 int /*<<< orphan*/  initkwds () ; 
 int /*<<< orphan*/  initspaces () ; 
 int /*<<< orphan*/ * m4wraps ; 
 int /*<<< orphan*/  macro () ; 
 int /*<<< orphan*/  macro_popdef (char*) ; 
 int /*<<< orphan*/  mark_traced (char*,int) ; 
 int maxout ; 
 int mimic_gnu ; 
 int /*<<< orphan*/  mstack ; 
 scalar_t__ onintr ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/ ** outfile ; 
 int /*<<< orphan*/  pbstr (int /*<<< orphan*/ ) ; 
 int prefix_builtins ; 
 int /*<<< orphan*/  release_input (scalar_t__) ; 
 int /*<<< orphan*/  resizedivs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_input (scalar_t__,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  set_trace_flags (char*) ; 
 int /*<<< orphan*/  setup_builtin (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ signal (int /*<<< orphan*/ ,scalar_t__) ; 
 int sp ; 
 int /*<<< orphan*/  sstack ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ stdout ; 
 int synch_lines ; 
 int /*<<< orphan*/  trace_file (char*) ; 
 int /*<<< orphan*/  usage () ; 
 int wrapindex ; 
 int /*<<< orphan*/  xalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xreallocarray (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int
main(int argc, char *argv[])
{
	int c;
	int n;
	char *p;

	if (signal(SIGINT, SIG_IGN) != SIG_IGN)
		signal(SIGINT, onintr);

	init_macros();
	initspaces();
	STACKMAX = INITSTACKMAX;

	mstack = xreallocarray(NULL, STACKMAX, sizeof(stae), NULL);
	sstack = xalloc(STACKMAX, NULL);

	maxout = 0;
	outfile = NULL;
	resizedivs(MAXOUT);

	while ((c = getopt(argc, argv, "gst:d:D:EU:o:I:P")) != -1)
		switch(c) {

		case 'D':               /* define something..*/
			for (p = optarg; *p; p++)
				if (*p == '=')
					break;
			if (*p)
				*p++ = EOS;
			dodefine(optarg, p);
			break;
		case 'E':               /* like GNU m4 1.4.9+ */
			if (error_warns == 0)
				error_warns = 1;
			else
				fatal_warns = 1;
			break;
		case 'I':
			addtoincludepath(optarg);
			break;
		case 'P':
			prefix_builtins = 1;
			break;
		case 'U':               /* undefine...       */
			macro_popdef(optarg);
			break;
		case 'g':
			mimic_gnu = 1;
			break;
		case 'd':
			set_trace_flags(optarg);
			break;
		case 's':
			synch_lines = 1;
			break;
		case 't':
			mark_traced(optarg, 1);
			break;
		case 'o':
			trace_file(optarg);
                        break;
		case '?':
			usage();
		}

        argc -= optind;
        argv += optind;

	initkwds();
	if (mimic_gnu)
		setup_builtin("format", FORMATTYPE);

	active = stdout;		/* default active output     */
	bbase[0] = bufbase;
        if (!argc) {
		sp = -1;		/* stack pointer initialized */
		fp = 0;			/* frame pointer initialized */
		set_input(infile+0, stdin, "stdin");
					/* default input (naturally) */
		macro();
	} else
		for (; argc--; ++argv) {
			p = *argv;
			if (p[0] == '-' && p[1] == EOS)
				set_input(infile, stdin, "stdin");
			else if (fopen_trypath(infile, p) == NULL)
				err(1, "%s", p);
			sp = -1;
			fp = 0;
			macro();
			release_input(infile);
		}

	if (wrapindex) {
		int i;

		ilevel = 0;		/* in case m4wrap includes.. */
		bufbase = bp = buf;	/* use the entire buffer   */
		if (mimic_gnu) {
			while (wrapindex != 0) {
				for (i = 0; i < wrapindex; i++)
					pbstr(m4wraps[i]);
				wrapindex =0;
				macro();
			}
		} else {
			for (i = 0; i < wrapindex; i++) {
				pbstr(m4wraps[i]);
				macro();
			}
		}
	}

	if (active != stdout)
		active = stdout;	/* reset output just in case */
	for (n = 1; n < maxout; n++)	/* default wrap-up: undivert */
		if (outfile[n] != NULL)
			getdiv(n);
					/* remove bitbucket if used  */
	if (outfile[0] != NULL) {
		(void) fclose(outfile[0]);
	}

	return exit_code;
}