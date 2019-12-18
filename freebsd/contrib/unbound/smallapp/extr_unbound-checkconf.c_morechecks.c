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
struct config_file {scalar_t__ verbosity; int num_threads; scalar_t__ edns_buffer_size; scalar_t__ msg_buffer_size; char* chrootdir; char* directory; char* pidfile; char* logfile; char* module_conf; char* username; char* control_key_file; char* control_cert_file; int /*<<< orphan*/  server_cert_file; int /*<<< orphan*/  server_key_file; scalar_t__ control_use_cert; scalar_t__ remote_control_enable; int /*<<< orphan*/  ipsecmod_hook; scalar_t__ ipsecmod_enabled; int /*<<< orphan*/  dlv_anchor_file; int /*<<< orphan*/  trusted_keys_file_list; int /*<<< orphan*/  auto_trust_anchor_file_list; int /*<<< orphan*/  trust_anchor_file_list; int /*<<< orphan*/  root_hints; int /*<<< orphan*/  do_tcp; int /*<<< orphan*/  do_udp; scalar_t__ prefer_ip6; int /*<<< orphan*/  do_ip6; int /*<<< orphan*/  do_ip4; int /*<<< orphan*/  forwards; int /*<<< orphan*/  stubs; } ;

/* Variables and functions */
 int /*<<< orphan*/  aclchecks (struct config_file*) ; 
 char* basedir (char*) ; 
 int /*<<< orphan*/  check_chroot_filelist (char*,int /*<<< orphan*/ ,char*,struct config_file*) ; 
 int /*<<< orphan*/  check_chroot_filelist_wild (char*,int /*<<< orphan*/ ,char*,struct config_file*) ; 
 int /*<<< orphan*/  check_chroot_string (char*,int /*<<< orphan*/ *,char*,struct config_file*) ; 
 int /*<<< orphan*/  check_modules_exist (char*) ; 
 int /*<<< orphan*/  ecs_conf_checks (struct config_file*) ; 
 int /*<<< orphan*/  endpwent () ; 
 int /*<<< orphan*/  fatal_exit (char*,...) ; 
 char* fname_after_chroot (char*,struct config_file*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * getpwnam (char*) ; 
 int /*<<< orphan*/  interfacechecks (struct config_file*) ; 
 int /*<<< orphan*/  is_dir (char*) ; 
 int /*<<< orphan*/  is_file (char*) ; 
 int /*<<< orphan*/  localzonechecks (struct config_file*) ; 
 scalar_t__ options_remote_is_address (struct config_file*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 
 scalar_t__ strstr (char*,char*) ; 
 int /*<<< orphan*/  tcpconnlimitchecks (struct config_file*) ; 
 int /*<<< orphan*/  view_and_respipchecks (struct config_file*) ; 
 int /*<<< orphan*/  w_config_adjust_directory (struct config_file*) ; 
 int /*<<< orphan*/  warn_hosts (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
morechecks(struct config_file* cfg)
{
	warn_hosts("stub-host", cfg->stubs);
	warn_hosts("forward-host", cfg->forwards);
	interfacechecks(cfg);
	aclchecks(cfg);
	tcpconnlimitchecks(cfg);

	if(cfg->verbosity < 0)
		fatal_exit("verbosity value < 0");
	if(cfg->num_threads <= 0 || cfg->num_threads > 10000)
		fatal_exit("num_threads value weird");
	if(!cfg->do_ip4 && !cfg->do_ip6)
		fatal_exit("ip4 and ip6 are both disabled, pointless");
	if(!cfg->do_ip6 && cfg->prefer_ip6)
		fatal_exit("cannot prefer and disable ip6, pointless");
	if(!cfg->do_udp && !cfg->do_tcp)
		fatal_exit("udp and tcp are both disabled, pointless");
	if(cfg->edns_buffer_size > cfg->msg_buffer_size)
		fatal_exit("edns-buffer-size larger than msg-buffer-size, "
			"answers will not fit in processing buffer");
#ifdef UB_ON_WINDOWS
	w_config_adjust_directory(cfg);
#endif
	if(cfg->chrootdir && cfg->chrootdir[0] &&
		cfg->chrootdir[strlen(cfg->chrootdir)-1] == '/')
		fatal_exit("chootdir %s has trailing slash '/' please remove.",
			cfg->chrootdir);
	if(cfg->chrootdir && cfg->chrootdir[0] &&
		!is_dir(cfg->chrootdir)) {
		fatal_exit("bad chroot directory");
	}
	if(cfg->directory && cfg->directory[0]) {
		char* ad = fname_after_chroot(cfg->directory, cfg, 0);
		if(!ad) fatal_exit("out of memory");
		if(!is_dir(ad)) fatal_exit("bad chdir directory");
		free(ad);
	}
	if( (cfg->chrootdir && cfg->chrootdir[0]) ||
	    (cfg->directory && cfg->directory[0])) {
		if(cfg->pidfile && cfg->pidfile[0]) {
			char* ad = (cfg->pidfile[0]=='/')?strdup(cfg->pidfile):
				fname_after_chroot(cfg->pidfile, cfg, 1);
			char* bd = basedir(ad);
			if(bd && !is_dir(bd))
				fatal_exit("pidfile directory does not exist");
			free(ad);
		}
		if(cfg->logfile && cfg->logfile[0]) {
			char* ad = fname_after_chroot(cfg->logfile, cfg, 1);
			char* bd = basedir(ad);
			if(bd && !is_dir(bd))
				fatal_exit("logfile directory does not exist");
			free(ad);
		}
	}

	check_chroot_filelist("file with root-hints",
		cfg->root_hints, cfg->chrootdir, cfg);
	check_chroot_filelist("trust-anchor-file",
		cfg->trust_anchor_file_list, cfg->chrootdir, cfg);
	check_chroot_filelist("auto-trust-anchor-file",
		cfg->auto_trust_anchor_file_list, cfg->chrootdir, cfg);
	check_chroot_filelist_wild("trusted-keys-file",
		cfg->trusted_keys_file_list, cfg->chrootdir, cfg);
	check_chroot_string("dlv-anchor-file", &cfg->dlv_anchor_file,
		cfg->chrootdir, cfg);
#ifdef USE_IPSECMOD
	if(cfg->ipsecmod_enabled && strstr(cfg->module_conf, "ipsecmod")) {
		/* only check hook if enabled */
		check_chroot_string("ipsecmod-hook", &cfg->ipsecmod_hook,
			cfg->chrootdir, cfg);
	}
#endif
	/* remove chroot setting so that modules are not stripping pathnames*/
	free(cfg->chrootdir);
	cfg->chrootdir = NULL;

	/* check that the modules listed in module_conf exist */
	check_modules_exist(cfg->module_conf);

	/* There should be no reason for 'respip' module not to work with
	 * dns64, but it's not explicitly confirmed,  so the combination is
	 * excluded below.   It's simply unknown yet for the combination of
	 * respip and other modules. */
	if(strcmp(cfg->module_conf, "iterator") != 0
		&& strcmp(cfg->module_conf, "validator iterator") != 0
		&& strcmp(cfg->module_conf, "dns64 validator iterator") != 0
		&& strcmp(cfg->module_conf, "dns64 iterator") != 0
		&& strcmp(cfg->module_conf, "respip iterator") != 0
		&& strcmp(cfg->module_conf, "respip validator iterator") != 0
#ifdef WITH_PYTHONMODULE
		&& strcmp(cfg->module_conf, "python iterator") != 0
		&& strcmp(cfg->module_conf, "python validator iterator") != 0
		&& strcmp(cfg->module_conf, "validator python iterator") != 0
		&& strcmp(cfg->module_conf, "dns64 python iterator") != 0
		&& strcmp(cfg->module_conf, "dns64 python validator iterator") != 0
		&& strcmp(cfg->module_conf, "dns64 validator python iterator") != 0
		&& strcmp(cfg->module_conf, "python dns64 iterator") != 0
		&& strcmp(cfg->module_conf, "python dns64 validator iterator") != 0
#endif
#ifdef USE_CACHEDB
		&& strcmp(cfg->module_conf, "validator cachedb iterator") != 0
		&& strcmp(cfg->module_conf, "cachedb iterator") != 0
		&& strcmp(cfg->module_conf, "dns64 validator cachedb iterator") != 0
		&& strcmp(cfg->module_conf, "dns64 cachedb iterator") != 0
#endif
#if defined(WITH_PYTHONMODULE) && defined(USE_CACHEDB)
		&& strcmp(cfg->module_conf, "python dns64 cachedb iterator") != 0
		&& strcmp(cfg->module_conf, "python dns64 validator cachedb iterator") != 0
		&& strcmp(cfg->module_conf, "dns64 python cachedb iterator") != 0
		&& strcmp(cfg->module_conf, "dns64 python validator cachedb iterator") != 0
		&& strcmp(cfg->module_conf, "python cachedb iterator") != 0
		&& strcmp(cfg->module_conf, "python validator cachedb iterator") != 0
		&& strcmp(cfg->module_conf, "cachedb python iterator") != 0
		&& strcmp(cfg->module_conf, "validator cachedb python iterator") != 0
		&& strcmp(cfg->module_conf, "validator python cachedb iterator") != 0
#endif
#ifdef CLIENT_SUBNET
		&& strcmp(cfg->module_conf, "subnetcache iterator") != 0
		&& strcmp(cfg->module_conf, "subnetcache validator iterator") != 0
		&& strcmp(cfg->module_conf, "dns64 subnetcache iterator") != 0
		&& strcmp(cfg->module_conf, "dns64 subnetcache validator iterator") != 0
#endif
#if defined(WITH_PYTHONMODULE) && defined(CLIENT_SUBNET)
		&& strcmp(cfg->module_conf, "python subnetcache iterator") != 0
		&& strcmp(cfg->module_conf, "subnetcache python iterator") != 0
		&& strcmp(cfg->module_conf, "python subnetcache validator iterator") != 0
		&& strcmp(cfg->module_conf, "subnetcache python validator iterator") != 0
		&& strcmp(cfg->module_conf, "subnetcache validator python iterator") != 0
#endif
#ifdef USE_IPSECMOD
		&& strcmp(cfg->module_conf, "ipsecmod iterator") != 0
		&& strcmp(cfg->module_conf, "ipsecmod validator iterator") != 0
#endif
#if defined(WITH_PYTHONMODULE) && defined(USE_IPSECMOD)
		&& strcmp(cfg->module_conf, "python ipsecmod iterator") != 0
		&& strcmp(cfg->module_conf, "ipsecmod python iterator") != 0
		&& strcmp(cfg->module_conf, "ipsecmod validator iterator") != 0
		&& strcmp(cfg->module_conf, "python ipsecmod validator iterator") != 0
		&& strcmp(cfg->module_conf, "ipsecmod python validator iterator") != 0
		&& strcmp(cfg->module_conf, "ipsecmod validator python iterator") != 0
#endif
		) {
		fatal_exit("module conf '%s' is not known to work",
			cfg->module_conf);
	}

#ifdef HAVE_GETPWNAM
	if(cfg->username && cfg->username[0]) {
		if(getpwnam(cfg->username) == NULL)
			fatal_exit("user '%s' does not exist.", cfg->username);
#  ifdef HAVE_ENDPWENT
		endpwent();
#  endif
	}
#endif
	if(cfg->remote_control_enable && options_remote_is_address(cfg)
		&& cfg->control_use_cert) {
		check_chroot_string("server-key-file", &cfg->server_key_file,
			cfg->chrootdir, cfg);
		check_chroot_string("server-cert-file", &cfg->server_cert_file,
			cfg->chrootdir, cfg);
		if(!is_file(cfg->control_key_file))
			fatal_exit("control-key-file: \"%s\" does not exist",
				cfg->control_key_file);
		if(!is_file(cfg->control_cert_file))
			fatal_exit("control-cert-file: \"%s\" does not exist",
				cfg->control_cert_file);
	}

	localzonechecks(cfg);
	view_and_respipchecks(cfg);
#ifdef CLIENT_SUBNET
	ecs_conf_checks(cfg);
#endif
}