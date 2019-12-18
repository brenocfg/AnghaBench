#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uid_t ;
struct passwd {int dummy; } ;
struct daemon {char* pidfile; void* chroot; int /*<<< orphan*/  connect_sslctx; int /*<<< orphan*/  listen_sslctx; int /*<<< orphan*/  rc; } ;
struct TYPE_3__ {TYPE_2__* first; } ;
struct config_file {char* username; char* chrootdir; char* pidfile; char* directory; scalar_t__ use_syslog; int /*<<< orphan*/  logfile; scalar_t__ do_daemonize; int /*<<< orphan*/  tls_win_cert; int /*<<< orphan*/  tls_cert_bundle; TYPE_1__ tls_session_ticket_keys; scalar_t__* tls_ciphersuites; scalar_t__* tls_ciphers; int /*<<< orphan*/  ssl_service_pem; scalar_t__* ssl_service_key; } ;
struct TYPE_4__ {scalar_t__* str; } ;

/* Variables and functions */
 scalar_t__ LOGIN_SETALL ; 
 unsigned int LOGIN_SETGROUP ; 
 unsigned int LOGIN_SETUSER ; 
 int /*<<< orphan*/  SSL_CTX_set_cipher_list (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  SSL_CTX_set_ciphersuites (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  VERB_QUERY ; 
 scalar_t__ cfg_gid ; 
 scalar_t__ cfg_uid ; 
 scalar_t__ chdir (char*) ; 
 int /*<<< orphan*/  checkoldpid (char*,int) ; 
 int chown (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ chroot (char*) ; 
 int /*<<< orphan*/  connect_sslctx_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  daemon_remote_create (struct config_file*) ; 
 int /*<<< orphan*/  detach () ; 
 int /*<<< orphan*/  endpwent () ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatal_exit (char*,...) ; 
 char* fname_after_chroot (char*,struct config_file*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  getpid () ; 
 struct passwd* getpwnam (char*) ; 
 scalar_t__ initgroups (char*,scalar_t__) ; 
 int /*<<< orphan*/  listen_sslctx_create (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listen_sslctx_setup_ticket_keys (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  log_init (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  log_warn (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ setgid (scalar_t__) ; 
 scalar_t__ setregid (scalar_t__,scalar_t__) ; 
 scalar_t__ setresgid (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ setresuid (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ setreuid (scalar_t__,scalar_t__) ; 
 scalar_t__ setuid (scalar_t__) ; 
 scalar_t__ setusercontext (int /*<<< orphan*/ *,struct passwd*,scalar_t__,unsigned int) ; 
 void* strdup (char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  w_config_adjust_directory (struct config_file*) ; 
 int /*<<< orphan*/  writepid (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
perform_setup(struct daemon* daemon, struct config_file* cfg, int debug_mode,
	const char** cfgfile, int need_pidfile)
{
#ifdef HAVE_KILL
	int pidinchroot;
#endif
#ifdef HAVE_GETPWNAM
	struct passwd *pwd = NULL;

	if(cfg->username && cfg->username[0]) {
		if((pwd = getpwnam(cfg->username)) == NULL)
			fatal_exit("user '%s' does not exist.", cfg->username);
		/* endpwent below, in case we need pwd for setusercontext */
	}
#endif
#ifdef UB_ON_WINDOWS
	w_config_adjust_directory(cfg);
#endif

	/* read ssl keys while superuser and outside chroot */
#ifdef HAVE_SSL
	if(!(daemon->rc = daemon_remote_create(cfg)))
		fatal_exit("could not set up remote-control");
	if(cfg->ssl_service_key && cfg->ssl_service_key[0]) {
		if(!(daemon->listen_sslctx = listen_sslctx_create(
			cfg->ssl_service_key, cfg->ssl_service_pem, NULL)))
			fatal_exit("could not set up listen SSL_CTX");
		if(cfg->tls_ciphers && cfg->tls_ciphers[0]) {
			if (!SSL_CTX_set_cipher_list(daemon->listen_sslctx, cfg->tls_ciphers)) {
				fatal_exit("failed to set tls-cipher %s", cfg->tls_ciphers);
			}
		}
#ifdef HAVE_SSL_CTX_SET_CIPHERSUITES
		if(cfg->tls_ciphersuites && cfg->tls_ciphersuites[0]) {
			if (!SSL_CTX_set_ciphersuites(daemon->listen_sslctx, cfg->tls_ciphersuites)) {
				fatal_exit("failed to set tls-ciphersuites %s", cfg->tls_ciphersuites);
			}
		}
#endif
		if(cfg->tls_session_ticket_keys.first &&
			cfg->tls_session_ticket_keys.first->str[0] != 0) {
			if(!listen_sslctx_setup_ticket_keys(daemon->listen_sslctx, cfg->tls_session_ticket_keys.first)) {
				fatal_exit("could not set session ticket SSL_CTX");
			}
		}
	}
	if(!(daemon->connect_sslctx = connect_sslctx_create(NULL, NULL,
		cfg->tls_cert_bundle, cfg->tls_win_cert)))
		fatal_exit("could not set up connect SSL_CTX");
#endif

	/* init syslog (as root) if needed, before daemonize, otherwise
	 * a fork error could not be printed since daemonize closed stderr.*/
	if(cfg->use_syslog) {
		log_init(cfg->logfile, cfg->use_syslog, cfg->chrootdir);
	}
	/* if using a logfile, we cannot open it because the logfile would
	 * be created with the wrong permissions, we cannot chown it because
	 * we cannot chown system logfiles, so we do not open at all.
	 * So, using a logfile, the user does not see errors unless -d is
	 * given to unbound on the commandline. */

#ifdef HAVE_KILL
	/* true if pidfile is inside chrootdir, or nochroot */
	pidinchroot = need_pidfile && (!(cfg->chrootdir && cfg->chrootdir[0]) ||
				(cfg->chrootdir && cfg->chrootdir[0] &&
				strncmp(cfg->pidfile, cfg->chrootdir,
				strlen(cfg->chrootdir))==0));

	/* check old pid file before forking */
	if(cfg->pidfile && cfg->pidfile[0] && need_pidfile) {
		/* calculate position of pidfile */
		if(cfg->pidfile[0] == '/')
			daemon->pidfile = strdup(cfg->pidfile);
		else	daemon->pidfile = fname_after_chroot(cfg->pidfile, 
				cfg, 1);
		if(!daemon->pidfile)
			fatal_exit("pidfile alloc: out of memory");
		checkoldpid(daemon->pidfile, pidinchroot);
	}
#endif

	/* daemonize because pid is needed by the writepid func */
	if(!debug_mode && cfg->do_daemonize) {
		detach();
	}

	/* write new pidfile (while still root, so can be outside chroot) */
#ifdef HAVE_KILL
	if(cfg->pidfile && cfg->pidfile[0] && need_pidfile) {
		writepid(daemon->pidfile, getpid());
		if(cfg->username && cfg->username[0] && cfg_uid != (uid_t)-1 &&
			pidinchroot) {
#  ifdef HAVE_CHOWN
			if(chown(daemon->pidfile, cfg_uid, cfg_gid) == -1) {
				verbose(VERB_QUERY, "cannot chown %u.%u %s: %s",
					(unsigned)cfg_uid, (unsigned)cfg_gid,
					daemon->pidfile, strerror(errno));
			}
#  endif /* HAVE_CHOWN */
		}
	}
#else
	(void)daemon;
	(void)need_pidfile;
#endif /* HAVE_KILL */

	/* Set user context */
#ifdef HAVE_GETPWNAM
	if(cfg->username && cfg->username[0] && cfg_uid != (uid_t)-1) {
#ifdef HAVE_SETUSERCONTEXT
		/* setusercontext does initgroups, setuid, setgid, and
		 * also resource limits from login config, but we
		 * still call setresuid, setresgid to be sure to set all uid*/
		if(setusercontext(NULL, pwd, cfg_uid, (unsigned)
			LOGIN_SETALL & ~LOGIN_SETUSER & ~LOGIN_SETGROUP) != 0)
			log_warn("unable to setusercontext %s: %s",
				cfg->username, strerror(errno));
#endif /* HAVE_SETUSERCONTEXT */
	}
#endif /* HAVE_GETPWNAM */

	/* box into the chroot */
#ifdef HAVE_CHROOT
	if(cfg->chrootdir && cfg->chrootdir[0]) {
		if(chdir(cfg->chrootdir)) {
			fatal_exit("unable to chdir to chroot %s: %s",
				cfg->chrootdir, strerror(errno));
		}
		verbose(VERB_QUERY, "chdir to %s", cfg->chrootdir);
		if(chroot(cfg->chrootdir))
			fatal_exit("unable to chroot to %s: %s", 
				cfg->chrootdir, strerror(errno));
		if(chdir("/"))
			fatal_exit("unable to chdir to / in chroot %s: %s",
				cfg->chrootdir, strerror(errno));
		verbose(VERB_QUERY, "chroot to %s", cfg->chrootdir);
		if(strncmp(*cfgfile, cfg->chrootdir, 
			strlen(cfg->chrootdir)) == 0) 
			(*cfgfile) += strlen(cfg->chrootdir);

		/* adjust stored pidfile for chroot */
		if(daemon->pidfile && daemon->pidfile[0] && 
			strncmp(daemon->pidfile, cfg->chrootdir,
			strlen(cfg->chrootdir))==0) {
			char* old = daemon->pidfile;
			daemon->pidfile = strdup(old+strlen(cfg->chrootdir));
			free(old);
			if(!daemon->pidfile)
				log_err("out of memory in pidfile adjust");
		}
		daemon->chroot = strdup(cfg->chrootdir);
		if(!daemon->chroot)
			log_err("out of memory in daemon chroot dir storage");
	}
#else
	(void)cfgfile;
#endif
	/* change to working directory inside chroot */
	if(cfg->directory && cfg->directory[0]) {
		char* dir = cfg->directory;
		if(cfg->chrootdir && cfg->chrootdir[0] &&
			strncmp(dir, cfg->chrootdir, 
			strlen(cfg->chrootdir)) == 0)
			dir += strlen(cfg->chrootdir);
		if(dir[0]) {
			if(chdir(dir)) {
				fatal_exit("Could not chdir to %s: %s",
					dir, strerror(errno));
			}
			verbose(VERB_QUERY, "chdir to %s", dir);
		}
	}

	/* drop permissions after chroot, getpwnam, pidfile, syslog done*/
#ifdef HAVE_GETPWNAM
	if(cfg->username && cfg->username[0] && cfg_uid != (uid_t)-1) {
#  ifdef HAVE_INITGROUPS
		if(initgroups(cfg->username, cfg_gid) != 0)
			log_warn("unable to initgroups %s: %s",
				cfg->username, strerror(errno));
#  endif /* HAVE_INITGROUPS */
#  ifdef HAVE_ENDPWENT
		endpwent();
#  endif

#ifdef HAVE_SETRESGID
		if(setresgid(cfg_gid,cfg_gid,cfg_gid) != 0)
#elif defined(HAVE_SETREGID) && !defined(DARWIN_BROKEN_SETREUID)
		if(setregid(cfg_gid,cfg_gid) != 0)
#else /* use setgid */
		if(setgid(cfg_gid) != 0)
#endif /* HAVE_SETRESGID */
			fatal_exit("unable to set group id of %s: %s", 
				cfg->username, strerror(errno));
#ifdef HAVE_SETRESUID
		if(setresuid(cfg_uid,cfg_uid,cfg_uid) != 0)
#elif defined(HAVE_SETREUID) && !defined(DARWIN_BROKEN_SETREUID)
		if(setreuid(cfg_uid,cfg_uid) != 0)
#else /* use setuid */
		if(setuid(cfg_uid) != 0)
#endif /* HAVE_SETRESUID */
			fatal_exit("unable to set user id of %s: %s", 
				cfg->username, strerror(errno));
		verbose(VERB_QUERY, "drop user privileges, run as %s", 
			cfg->username);
	}
#endif /* HAVE_GETPWNAM */
	/* file logging inited after chroot,chdir,setuid is done so that 
	 * it would succeed on SIGHUP as well */
	if(!cfg->use_syslog)
		log_init(cfg->logfile, cfg->use_syslog, cfg->chrootdir);
}