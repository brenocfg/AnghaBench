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
struct sigaction {int /*<<< orphan*/  sa_handler; } ;
struct dpv_file_node {char* name; int length; char* path; struct dpv_file_node* next; } ;
struct dpv_config {char* backtitle; scalar_t__ display_type; char* status_solo; char* status_many; int label_size; char* output; int display_limit; int pbar_size; char* title; int status_updates_per_second; void* keep_tite; int /*<<< orphan*/  action; void* output_type; int /*<<< orphan*/  options; int /*<<< orphan*/ * pprompt; void* debug; int /*<<< orphan*/ * aprompt; } ;

/* Variables and functions */
 void* BYTE_STATUS_SOLO ; 
 size_t DPV_APROMPT_MAX ; 
 scalar_t__ DPV_DISPLAY_DIALOG ; 
 scalar_t__ DPV_DISPLAY_LIBDIALOG ; 
 scalar_t__ DPV_DISPLAY_XDIALOG ; 
 int /*<<< orphan*/  DPV_NO_OVERRUN ; 
 void* DPV_OUTPUT_FILE ; 
 void* DPV_OUTPUT_SHELL ; 
 size_t DPV_PPROMPT_MAX ; 
 int /*<<< orphan*/  DPV_TEST_MODE ; 
 int /*<<< orphan*/  DPV_WIDE_MODE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 void* LINE_STATUS_SOLO ; 
 int /*<<< orphan*/  SIGINT ; 
 void* TRUE ; 
 void* debug ; 
 scalar_t__ dpv (struct dpv_config*,struct dpv_file_node*) ; 
 int /*<<< orphan*/  dpv_free () ; 
 int /*<<< orphan*/  end_dialog () ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 struct dpv_file_node* file_list ; 
 int /*<<< orphan*/  free (char*) ; 
 int getopt (int,char**,char*) ; 
 void* line_mode ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  memset (void*,char,size_t) ; 
 void* multiple ; 
 scalar_t__ nfiles ; 
 void* no_overrun ; 
 int /*<<< orphan*/  operate_on_bytes ; 
 int /*<<< orphan*/  operate_on_lines ; 
 char* optarg ; 
 scalar_t__ optind ; 
 void* output_type ; 
 char* pgm ; 
 int /*<<< orphan*/  sig_int ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,size_t,char*,char*) ; 
 int sscanf (char*,char*,int*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strtol (char*,char**,int) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
main(int argc, char *argv[])
{
	char dummy;
	int ch;
	int n = 0;
	size_t config_size = sizeof(struct dpv_config);
	size_t file_node_size = sizeof(struct dpv_file_node);
	struct dpv_config *config;
	struct dpv_file_node *curfile;
	struct sigaction act;

	pgm = argv[0]; /* store a copy of invocation name */

	/* Allocate config structure */
	if ((config = malloc(config_size)) == NULL)
		errx(EXIT_FAILURE, "Out of memory?!");
	memset((void *)(config), '\0', config_size);

	/*
	 * Process command-line options
	 */
	while ((ch = getopt(argc, argv,
	    "a:b:dDhi:I:klL:mn:No:p:P:t:TU:wx:X")) != -1) {
		switch(ch) {
		case 'a': /* additional message text to append */
			if (config->aprompt == NULL) {
				config->aprompt = malloc(DPV_APROMPT_MAX);
				if (config->aprompt == NULL)
					errx(EXIT_FAILURE, "Out of memory?!");
			}
			snprintf(config->aprompt, DPV_APROMPT_MAX, "%s",
			    optarg);
			break;
		case 'b': /* [X]dialog(1) backtitle */
			if (config->backtitle != NULL)
				free((char *)config->backtitle);
			config->backtitle = malloc(strlen(optarg) + 1);
			if (config->backtitle == NULL)
				errx(EXIT_FAILURE, "Out of memory?!");
			*(config->backtitle) = '\0';
			strcat(config->backtitle, optarg);
			break;
		case 'd': /* debugging */
			debug = TRUE;
			config->debug = debug;
			break;
		case 'D': /* use dialog(1) instead of libdialog */
			config->display_type = DPV_DISPLAY_DIALOG;
			break;
		case 'h': /* help/usage */
			usage();
			break; /* NOTREACHED */
		case 'i': /* status line format string for single-file */
			config->status_solo = optarg;
			break;
		case 'I': /* status line format string for many-files */
			config->status_many = optarg;
			break;
		case 'k': /* keep tite */
			config->keep_tite = TRUE;
			break;
		case 'l': /* Line mode */
			line_mode = TRUE;
			break;
		case 'L': /* custom label size */
			config->label_size =
			    (int)strtol(optarg, (char **)NULL, 10);
			if (config->label_size == 0 && errno == EINVAL)
				errx(EXIT_FAILURE,
				    "`-L' argument must be numeric");
			else if (config->label_size < -1)
				config->label_size = -1;
			break;
		case 'm': /* enable multiple file arguments */
			multiple = TRUE;
			break;
		case 'o': /* `-o path' for sending data-read to file */
			output_type = DPV_OUTPUT_FILE;
			config->output_type = DPV_OUTPUT_FILE;
			config->output = optarg;
			break;
		case 'n': /* custom number of files per `page' */
			config->display_limit =
				(int)strtol(optarg, (char **)NULL, 10);
			if (config->display_limit == 0 && errno == EINVAL)
				errx(EXIT_FAILURE,
				    "`-n' argument must be numeric");
			else if (config->display_limit < 0)
				config->display_limit = -1;
			break;
		case 'N': /* No overrun (truncate reads of known-length) */
			no_overrun = TRUE;
			config->options |= DPV_NO_OVERRUN;
			break;
		case 'p': /* additional message text to use as prefix */
			if (config->pprompt == NULL) {
				config->pprompt = malloc(DPV_PPROMPT_MAX + 2);
				if (config->pprompt == NULL)
					errx(EXIT_FAILURE, "Out of memory?!");
				/* +2 is for implicit "\n" appended later */
			}
			snprintf(config->pprompt, DPV_PPROMPT_MAX, "%s",
			    optarg);
			break;
		case 'P': /* custom size for mini-progressbar */
			config->pbar_size =
			    (int)strtol(optarg, (char **)NULL, 10);
			if (config->pbar_size == 0 && errno == EINVAL)
				errx(EXIT_FAILURE,
				    "`-P' argument must be numeric");
			else if (config->pbar_size < -1)
				config->pbar_size = -1;
			break;
		case 't': /* [X]dialog(1) title */
			if (config->title != NULL)
				free(config->title);
			config->title = malloc(strlen(optarg) + 1);
			if (config->title == NULL)
				errx(EXIT_FAILURE, "Out of memory?!");
			*(config->title) = '\0';
			strcat(config->title, optarg);
			break;
		case 'T': /* test mode (don't read data, fake it) */
			config->options |= DPV_TEST_MODE;
			break;
		case 'U': /* updates per second */
			config->status_updates_per_second =
			    (int)strtol(optarg, (char **)NULL, 10);
			if (config->status_updates_per_second == 0 &&
			    errno == EINVAL)
				errx(EXIT_FAILURE,
				    "`-U' argument must be numeric");
			break;
		case 'w': /* `-p' and `-a' widths bump [X]dialog(1) width */
			config->options |= DPV_WIDE_MODE;
			break;
		case 'x': /* `-x cmd' for sending data-read to sh(1) code */
			output_type = DPV_OUTPUT_SHELL;
			config->output_type = DPV_OUTPUT_SHELL;
			config->output = optarg;
			break;
		case 'X': /* X11 support through x11/xdialog */
			config->display_type = DPV_DISPLAY_XDIALOG;
			break;
		case '?': /* unknown argument (based on optstring) */
			/* FALLTHROUGH */
		default: /* unhandled argument (based on switch) */
			usage();
			/* NOTREACHED */
		}
	}
	argc -= optind;
	argv += optind;

	/* Process remaining arguments as list of names to display */
	for (curfile = file_list; n < argc; n++) {
		nfiles++;

		/* Allocate a new struct for the file argument */
		if (curfile == NULL) {
			if ((curfile = malloc(file_node_size)) == NULL)
				errx(EXIT_FAILURE, "Out of memory?!");
			memset((void *)(curfile), '\0', file_node_size);
			file_list = curfile;
		} else {
			if ((curfile->next = malloc(file_node_size)) == NULL)
				errx(EXIT_FAILURE, "Out of memory?!");
			memset((void *)(curfile->next), '\0', file_node_size);
			curfile = curfile->next;
		}
		curfile->name = argv[n];

		/* Read possible `lines:' prefix from label syntax */
		if (sscanf(curfile->name, "%lli:%c", &(curfile->length),
		    &dummy) == 2)
			curfile->name = strchr(curfile->name, ':') + 1;
		else
			curfile->length = -1;

		/* Read path argument if enabled */
		if (multiple) {
			if (++n >= argc)
				errx(EXIT_FAILURE, "Missing path argument "
				    "for label number %i", nfiles);
			curfile->path = argv[n];
		} else
			break;
	}

	/* Display usage and exit if not given at least one name */
	if (nfiles == 0) {
		warnx("no labels provided");
		usage();
		/* NOTREACHED */
	}

	/*
	 * Set cleanup routine for Ctrl-C action
	 */
	if (config->display_type == DPV_DISPLAY_LIBDIALOG) {
		act.sa_handler = sig_int;
		sigaction(SIGINT, &act, 0);
	}

	/* Set status formats and action */
	if (line_mode) {
		config->status_solo = LINE_STATUS_SOLO;
		config->status_many = LINE_STATUS_SOLO;
		config->action = operate_on_lines;
	} else {
		config->status_solo = BYTE_STATUS_SOLO;
		config->status_many = BYTE_STATUS_SOLO;
		config->action = operate_on_bytes;
	}

	/*
	 * Hand off to dpv(3)...
	 */
	if (dpv(config, file_list) != 0 && debug)
		warnx("dpv(3) returned error!?");

	if (!config->keep_tite)
		end_dialog();
	dpv_free();

	exit(EXIT_SUCCESS);
}