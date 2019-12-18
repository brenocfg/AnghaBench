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
struct daemon {int dummy; } ;
struct config_file {scalar_t__ do_daemonize; scalar_t__ use_systemd; int /*<<< orphan*/ * logfile; scalar_t__ use_syslog; scalar_t__ verbosity; } ;

/* Variables and functions */
 int /*<<< orphan*/  checkrlimits (struct config_file*) ; 
 int /*<<< orphan*/  daemon_apply_cfg (struct daemon*,struct config_file*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_ident_set_fromdefault (struct config_file*,char const*) ; 
 int /*<<< orphan*/  log_warn (char*) ; 
 scalar_t__ verbosity ; 

__attribute__((used)) static void
apply_settings(struct daemon* daemon, struct config_file* cfg, 
	int cmdline_verbose, int debug_mode, const char* log_default_identity)
{
	/* apply if they have changed */
	verbosity = cmdline_verbose + cfg->verbosity;
	if (debug_mode > 1) {
		cfg->use_syslog = 0;
		free(cfg->logfile);
		cfg->logfile = NULL;
	}
	daemon_apply_cfg(daemon, cfg);
	checkrlimits(cfg);

	if (cfg->use_systemd && cfg->do_daemonize) {
		log_warn("use-systemd and do-daemonize should not be enabled at the same time");
	}

	log_ident_set_fromdefault(cfg, log_default_identity);
}