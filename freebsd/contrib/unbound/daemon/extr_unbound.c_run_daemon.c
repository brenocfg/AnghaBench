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
struct daemon {scalar_t__ pidfile; int /*<<< orphan*/  chroot; int /*<<< orphan*/  need_to_exit; } ;
struct config_file {int /*<<< orphan*/  chrootdir; int /*<<< orphan*/  logfile; int /*<<< orphan*/  use_syslog; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  PACKAGE_STRING ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  VERB_OPS ; 
 int /*<<< orphan*/  apply_settings (struct daemon*,struct config_file*,int,int,char const*) ; 
 int /*<<< orphan*/  close (int) ; 
 struct config_file* config_create () ; 
 int /*<<< orphan*/  config_delete (struct config_file*) ; 
 int /*<<< orphan*/  config_lookup_uid (struct config_file*) ; 
 int /*<<< orphan*/  config_read (struct config_file*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  daemon_cleanup (struct daemon*) ; 
 int /*<<< orphan*/  daemon_delete (struct daemon*) ; 
 int /*<<< orphan*/  daemon_fork (struct daemon*) ; 
 struct daemon* daemon_init () ; 
 int /*<<< orphan*/  daemon_open_shared_ports (struct daemon*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fatal_exit (char*,...) ; 
 int /*<<< orphan*/  log_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_warn (char*) ; 
 int open (scalar_t__,int,int) ; 
 int /*<<< orphan*/  perform_setup (struct daemon*,struct config_file*,int,char const**,int) ; 
 int /*<<< orphan*/  unlink (scalar_t__) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void 
run_daemon(const char* cfgfile, int cmdline_verbose, int debug_mode, const char* log_default_identity, int need_pidfile)
{
	struct config_file* cfg = NULL;
	struct daemon* daemon = NULL;
	int done_setup = 0;

	if(!(daemon = daemon_init()))
		fatal_exit("alloc failure");
	while(!daemon->need_to_exit) {
		if(done_setup)
			verbose(VERB_OPS, "Restart of %s.", PACKAGE_STRING);
		else	verbose(VERB_OPS, "Start of %s.", PACKAGE_STRING);

		/* config stuff */
		if(!(cfg = config_create()))
			fatal_exit("Could not alloc config defaults");
		if(!config_read(cfg, cfgfile, daemon->chroot)) {
			if(errno != ENOENT)
				fatal_exit("Could not read config file: %s."
					" Maybe try unbound -dd, it stays on "
					"the commandline to see more errors, "
					"or unbound-checkconf", cfgfile);
			log_warn("Continuing with default config settings");
		}
		apply_settings(daemon, cfg, cmdline_verbose, debug_mode, log_default_identity);
		if(!done_setup)
			config_lookup_uid(cfg);
	
		/* prepare */
		if(!daemon_open_shared_ports(daemon))
			fatal_exit("could not open ports");
		if(!done_setup) { 
			perform_setup(daemon, cfg, debug_mode, &cfgfile, need_pidfile);
			done_setup = 1; 
		} else {
			/* reopen log after HUP to facilitate log rotation */
			if(!cfg->use_syslog)
				log_init(cfg->logfile, 0, cfg->chrootdir);
		}
		/* work */
		daemon_fork(daemon);

		/* clean up for restart */
		verbose(VERB_ALGO, "cleanup.");
		daemon_cleanup(daemon);
		config_delete(cfg);
	}
	verbose(VERB_ALGO, "Exit cleanup.");
	/* this unlink may not work if the pidfile is located outside
	 * of the chroot/workdir or we no longer have permissions */
	if(daemon->pidfile) {
		int fd;
		/* truncate pidfile */
		fd = open(daemon->pidfile, O_WRONLY | O_TRUNC, 0644);
		if(fd != -1)
			close(fd);
		/* delete pidfile */
		unlink(daemon->pidfile);
	}
	daemon_delete(daemon);
}