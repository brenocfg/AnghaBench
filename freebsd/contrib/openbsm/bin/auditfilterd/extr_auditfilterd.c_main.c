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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* AUDITFILTERD_CONFFILE ; 
 char* AUDITFILTERD_PIPEFILE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ auditfilterd_conf (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  auditfilterd_conf_shutdown () ; 
 int /*<<< orphan*/  auditfilterd_init () ; 
 scalar_t__ daemon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  mainloop_file (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mainloop_pipe (char const*,char const*,int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_handler ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	const char *pipefile, *trailfile, *conffile;
	FILE *trail_fp, *conf_fp;
	struct stat sb;
	int pipe_fd;
	int ch;

	conffile = AUDITFILTERD_CONFFILE;
	trailfile = NULL;
	pipefile = NULL;
	while ((ch = getopt(argc, argv, "c:dp:t:")) != -1) {
		switch (ch) {
		case 'c':
			conffile = optarg;
			break;

		case 'd':
			debug++;
			break;

		case 't':
			if (trailfile != NULL || pipefile != NULL)
				usage();
			trailfile = optarg;
			break;

		case 'p':
			if (pipefile != NULL || trailfile != NULL)
				usage();
			pipefile = optarg;
			break;

		default:
			usage();
		}
	}

	argc -= optind;
	argv += optind;

	if (argc != 0)
		usage();

	/*
	 * We allow only one of a pipe or a trail to be used.  If none is
	 * specified, we provide a default pipe path.
	 */
	if (pipefile == NULL && trailfile == NULL)
		pipefile = AUDITFILTERD_PIPEFILE;

	if (pipefile != NULL) {
		pipe_fd = open(pipefile, O_RDONLY);
		if (pipe_fd < 0)
			err(-1, "open:%s", pipefile);
		if (fstat(pipe_fd, &sb) < 0)
			err(-1, "stat: %s", pipefile);
		if (!S_ISCHR(sb.st_mode))
			errx(-1, "fstat: %s not device", pipefile);
	} else {
		trail_fp = fopen(trailfile, "r");
		if (trail_fp == NULL)
			err(-1, "%s", trailfile);
	}

	conf_fp = fopen(conffile, "r");
	if (conf_fp == NULL)
		err(-1, "%s", conffile);

	auditfilterd_init();
	if (auditfilterd_conf(conffile, conf_fp) < 0)
		exit(-1);
	fclose(conf_fp);

	if (!debug) {
		if (daemon(0, 0) < 0)
			err(-1, "daemon");
	}

	signal(SIGHUP, signal_handler);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGTERM, signal_handler);

	if (pipefile != NULL)
		mainloop_pipe(conffile, pipefile, pipe_fd);
	else
		mainloop_file(conffile, trailfile, trail_fp);

	auditfilterd_conf_shutdown();
	return (0);
}