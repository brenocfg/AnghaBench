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
typedef  int /*<<< orphan*/  lock_quick_type ;

/* Variables and functions */
 char* CONFIGFILE ; 
 int /*<<< orphan*/  fatal_exit (char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  lock_quick_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ log_get_lock () ; 
 int /*<<< orphan*/  log_ident_set (char const*) ; 
 int /*<<< orphan*/  log_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  run_daemon (char const*,int,int,char const*,int) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  verbosity ; 
 int /*<<< orphan*/  wsvc_command_option (char const*,char const*,int,int) ; 

int 
main(int argc, char* argv[])
{
	int c;
	const char* cfgfile = CONFIGFILE;
	const char* winopt = NULL;
	const char* log_ident_default;
	int cmdline_verbose = 0;
	int debug_mode = 0;
	int need_pidfile = 1;

#ifdef UB_ON_WINDOWS
	int cmdline_cfg = 0;
#endif

	log_init(NULL, 0, NULL);
	log_ident_default = strrchr(argv[0],'/')?strrchr(argv[0],'/')+1:argv[0];
	log_ident_set(log_ident_default);
	/* parse the options */
	while( (c=getopt(argc, argv, "c:dhpvw:")) != -1) {
		switch(c) {
		case 'c':
			cfgfile = optarg;
#ifdef UB_ON_WINDOWS
			cmdline_cfg = 1;
#endif
			break;
		case 'v':
			cmdline_verbose++;
			verbosity++;
			break;
		case 'p':
			need_pidfile = 0;
			break;
		case 'd':
			debug_mode++;
			break;
		case 'w':
			winopt = optarg;
			break;
		case '?':
		case 'h':
		default:
			usage();
			return 1;
		}
	}
	argc -= optind;
	/* argv += optind; not using further arguments */

	if(winopt) {
#ifdef UB_ON_WINDOWS
		wsvc_command_option(winopt, cfgfile, cmdline_verbose, 
			cmdline_cfg);
#else
		fatal_exit("option not supported");
#endif
	}

	if(argc != 0) {
		usage();
		return 1;
	}

	run_daemon(cfgfile, cmdline_verbose, debug_mode, log_ident_default, need_pidfile);
	log_init(NULL, 0, NULL); /* close logfile */
#ifndef unbound_testbound
	if(log_get_lock()) {
		lock_quick_destroy((lock_quick_type*)log_get_lock());
	}
#endif
	return 0;
}