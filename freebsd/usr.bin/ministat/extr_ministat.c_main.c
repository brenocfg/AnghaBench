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
struct winsize {int ws_col; } ;
struct dataset {char* name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CAPH_READ ; 
 int /*<<< orphan*/  DimPlot (struct dataset*) ; 
 int /*<<< orphan*/  DumpPlot () ; 
 int MAX_DS ; 
 int NCONF ; 
 int /*<<< orphan*/  PlotSet (struct dataset*,int) ; 
 struct dataset* ReadSet (int /*<<< orphan*/ *,char const*,int,char const*) ; 
 int /*<<< orphan*/  Relative (struct dataset*,struct dataset*,int) ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  SetupPlot (int,int,int) ; 
 int /*<<< orphan*/  TIOCGWINSZ ; 
 int /*<<< orphan*/  Vitals (struct dataset*,int) ; 
 int /*<<< orphan*/  VitalsHead () ; 
 int atoi (char*) ; 
 scalar_t__ caph_enter () ; 
 scalar_t__ caph_limit_stdio () ; 
 scalar_t__ caph_limit_stream (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 char* getenv (char*) ; 
 int getopt (int,char**,char*) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct winsize*) ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 double strtod (char*,char**) ; 
 int strtol (char*,char**,int) ; 
 double* studentpct ; 
 int* symbol ; 
 int /*<<< orphan*/  usage (char*) ; 

int
main(int argc, char **argv)
{
	const char *setfilenames[MAX_DS - 1];
	struct dataset *ds[MAX_DS - 1];
	FILE *setfiles[MAX_DS - 1];
	int nds;
	double a;
	const char *delim = " \t";
	char *p;
	int c, i, ci;
	int column = 1;
	int flag_s = 0;
	int flag_n = 0;
	int termwidth = 74;
	int suppress_plot = 0;

	if (isatty(STDOUT_FILENO)) {
		struct winsize wsz;

		if ((p = getenv("COLUMNS")) != NULL && *p != '\0')
			termwidth = atoi(p);
		else if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsz) != -1 &&
			 wsz.ws_col > 0)
			termwidth = wsz.ws_col - 2;
	}

	ci = -1;
	while ((c = getopt(argc, argv, "AC:c:d:snw:")) != -1)
		switch (c) {
		case 'A':
			suppress_plot = 1;
			break;
		case 'C':
			column = strtol(optarg, &p, 10);
			if (p != NULL && *p != '\0')
				usage("Invalid column number.");
			if (column <= 0)
				usage("Column number should be positive.");
			break;
		case 'c':
			a = strtod(optarg, &p);
			if (p != NULL && *p != '\0')
				usage("Not a floating point number");
			for (i = 0; i < NCONF; i++)
				if (a == studentpct[i])
					ci = i;
			if (ci == -1)
				usage("No support for confidence level");
			break;
		case 'd':
			if (*optarg == '\0')
				usage("Can't use empty delimiter string");
			delim = optarg;
			break;
		case 'n':
			flag_n = 1;
			break;
		case 's':
			flag_s = 1;
			break;
		case 'w':
			termwidth = strtol(optarg, &p, 10);
			if (p != NULL && *p != '\0')
				usage("Invalid width, not a number.");
			if (termwidth < 0)
				usage("Unable to move beyond left margin.");
			break;
		default:
			usage("Unknown option");
			break;
		}
	if (ci == -1)
		ci = 2;
	argc -= optind;
	argv += optind;

	if (argc == 0) {
		setfilenames[0] = "<stdin>";
		setfiles[0] = stdin;
		nds = 1;
	} else {
		if (argc > (MAX_DS - 1))
			usage("Too many datasets.");
		nds = argc;
		for (i = 0; i < nds; i++) {
			setfilenames[i] = argv[i];
			if (!strcmp(argv[i], "-"))
				setfiles[0] = stdin;
			else
				setfiles[i] = fopen(argv[i], "r");
			if (setfiles[i] == NULL)
				err(2, "Cannot open %s", argv[i]);
		}
	}

	if (caph_limit_stdio() < 0)
		err(2, "capsicum");

	for (i = 0; i < nds; i++)
		if (caph_limit_stream(fileno(setfiles[i]), CAPH_READ) < 0)
			err(2, "unable to limit rights for %s",
			    setfilenames[i]);

	/* Enter Capsicum sandbox. */
	if (caph_enter() < 0)
		err(2, "unable to enter capability mode");

	for (i = 0; i < nds; i++) {
		ds[i] = ReadSet(setfiles[i], setfilenames[i], column, delim);
		if (setfiles[i] != stdin)
			fclose(setfiles[i]);
	}

	for (i = 0; i < nds; i++)
		printf("%c %s\n", symbol[i+1], ds[i]->name);

	if (!flag_n && !suppress_plot) {
		SetupPlot(termwidth, flag_s, nds);
		for (i = 0; i < nds; i++)
			DimPlot(ds[i]);
		for (i = 0; i < nds; i++)
			PlotSet(ds[i], i + 1);
		DumpPlot();
	}
	VitalsHead();
	Vitals(ds[0], 1);
	for (i = 1; i < nds; i++) {
		Vitals(ds[i], i + 1);
		if (!flag_n)
			Relative(ds[i], ds[0], ci);
	}
	exit(0);
}