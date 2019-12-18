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
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  LOG_LOCAL2 ; 
 int LOG_NDELAY ; 
 int LOG_PID ; 
 int /*<<< orphan*/  LOG_UPTO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  Verbose ; 
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chat_expect (char*) ; 
 char* chat_file ; 
 int /*<<< orphan*/  chat_send (char*) ; 
 char* copy_of (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_file (char*) ; 
 int /*<<< orphan*/  echo ; 
 int /*<<< orphan*/  fatal (int,char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  init () ; 
 int /*<<< orphan*/  openlog (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 char* phone_num ; 
 char* phone_num2 ; 
 char* report_file ; 
 int /*<<< orphan*/ * report_fp ; 
 int /*<<< orphan*/  setlogmask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/  terminate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timeout ; 
 scalar_t__ to_log ; 
 int /*<<< orphan*/  to_stderr ; 
 int /*<<< orphan*/  tzset () ; 
 int /*<<< orphan*/  usage () ; 
 scalar_t__ verbose ; 

int
main(int argc, char *argv[])
{
    int option;

    tzset();

    while ((option = getopt(argc, argv, "ef:r:sSt:T:U:vV")) != -1) {
	switch (option) {
	case 'e':
	    ++echo;
	    break;

	case 'f':
	    if (chat_file != NULL)
		free(chat_file);
	    chat_file = copy_of(optarg);
	    break;

	case 'r':
	    if (report_fp != NULL)
		fclose(report_fp);
	    if (report_file != NULL)
		free(report_file);
	    report_file = copy_of(optarg);
	    report_fp = fopen(report_file, "a");
	    if (report_fp != NULL) {
		if (verbose)
		    fprintf(report_fp, "Opening \"%s\"...\n", report_file);
	    } else
		fatal(2, "cannot open \"%s\" for appending", report_file);
	    break;

	case 's':
	    ++to_stderr;
	    break;

	case 'S':
	    to_log = 0;
	    break;

	case 't':
	    timeout = atoi(optarg);
	    break;

	case 'T':
	    if (phone_num != NULL)
		free(phone_num);
	    phone_num = copy_of(optarg);
	    break;

	case 'U':
	    if (phone_num2 != NULL)
		free(phone_num2);
	    phone_num2 = copy_of(optarg);
	    break;

	case 'v':
	    ++verbose;
	    break;

	case 'V':
	    ++Verbose;
	    break;

	default:
	    usage();
	    break;
	}
    }

    argc -= optind;
    argv += optind;

/*
 * Default the report file to the stderr location
 */
    if (report_fp == NULL)
	report_fp = stderr;

    if (to_log) {
	openlog("chat", LOG_PID | LOG_NDELAY, LOG_LOCAL2);

	if (verbose)
	    setlogmask(LOG_UPTO(LOG_INFO));
	else
	    setlogmask(LOG_UPTO(LOG_WARNING));
    }

    if (chat_file != NULL) {
	if (*argv != NULL)
	    usage();
	else {
            init();
	    do_file(chat_file);
	}
    } else {
	init();
	while (*argv != NULL && argc > 0) {
	    chat_expect(*argv);
	    argv++;
	    argc--;

	    if (*argv != NULL && argc > 0) {
		chat_send(*argv);
		argv++;
		argc--;
	    }
	}
    }

    terminate(0);
    return 0;
}