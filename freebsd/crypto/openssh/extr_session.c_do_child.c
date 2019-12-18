#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct ssh {int dummy; } ;
struct passwd {char* pw_shell; char* pw_dir; int /*<<< orphan*/  pw_name; } ;
typedef  int /*<<< orphan*/  cell ;
typedef  int /*<<< orphan*/  argv0 ;
struct TYPE_11__ {scalar_t__ kerberos_get_afs_token; scalar_t__ use_pam; } ;
struct TYPE_10__ {int ttyfd; scalar_t__ is_subsystem; struct passwd* pw; TYPE_1__* authctxt; int /*<<< orphan*/ * tty; } ;
struct TYPE_9__ {int /*<<< orphan*/  krb5_fwd_ccache; int /*<<< orphan*/ * krb5_ctx; scalar_t__ force_pwchange; } ;
typedef  TYPE_2__ Session ;

/* Variables and functions */
 int ARGV_MAX ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  INTERNAL_SFTP_NAME ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_DFL ; 
 scalar_t__ STDERR_FILENO ; 
 scalar_t__ SUBSYSTEM_INT_SFTP ; 
 scalar_t__ SUBSYSTEM_INT_SFTP_ERROR ; 
 char* _PATH_BSHELL ; 
 char* __progname ; 
 scalar_t__ chdir (char*) ; 
 int /*<<< orphan*/  check_quietlogin (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  child_close_fds (struct ssh*) ; 
 int /*<<< orphan*/  closefrom (scalar_t__) ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  debug3 (char*) ; 
 int /*<<< orphan*/  destroy_sensitive_data () ; 
 int /*<<< orphan*/  display_loginmsg () ; 
 int /*<<< orphan*/  do_motd () ; 
 int /*<<< orphan*/  do_nologin (struct passwd*) ; 
 int /*<<< orphan*/  do_pwchange (TYPE_2__*) ; 
 int /*<<< orphan*/  do_rc_files (struct ssh*,TYPE_2__*,char const*) ; 
 char** do_setup_env (struct ssh*,TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  do_setusercontext (struct passwd*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  execve (char const*,char**,char**) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  in_chroot ; 
 int /*<<< orphan*/  is_pam_session_open () ; 
 scalar_t__ k_afs_cell_of_file (char*,char*,int) ; 
 scalar_t__ k_hasafs () ; 
 int /*<<< orphan*/  k_setpag () ; 
 int /*<<< orphan*/  krb5_afslog (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_afslog_home (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lc ; 
 int login_getcapbool (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* login_getcapstr (int /*<<< orphan*/ ,char*,char*,char*) ; 
 TYPE_3__ options ; 
 int /*<<< orphan*/  packet_clear_keys () ; 
 int /*<<< orphan*/  perror (char const*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  session_setup_sia (struct passwd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setproctitle (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sftp_server_main (int,char**,struct passwd*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssh_selinux_change_context (char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int strlcpy (char*,char const*,int) ; 
 char* strrchr (char const*,char) ; 
 char* strtok (char*,char*) ; 
 char* xstrdup (char const*) ; 

void
do_child(struct ssh *ssh, Session *s, const char *command)
{
	extern char **environ;
	char **env;
	char *argv[ARGV_MAX];
	const char *shell, *shell0;
	struct passwd *pw = s->pw;
	int r = 0;

	/* remove hostkey from the child's memory */
	destroy_sensitive_data();
	packet_clear_keys();

	/* Force a password change */
	if (s->authctxt->force_pwchange) {
		do_setusercontext(pw);
		child_close_fds(ssh);
		do_pwchange(s);
		exit(1);
	}

	/*
	 * Login(1) does this as well, and it needs uid 0 for the "-h"
	 * switch, so we let login(1) to this for us.
	 */
#ifdef HAVE_OSF_SIA
	session_setup_sia(pw, s->ttyfd == -1 ? NULL : s->tty);
	if (!check_quietlogin(s, command))
		do_motd();
#else /* HAVE_OSF_SIA */
	/* When PAM is enabled we rely on it to do the nologin check */
	if (!options.use_pam)
		do_nologin(pw);
	do_setusercontext(pw);
	/*
	 * PAM session modules in do_setusercontext may have
	 * generated messages, so if this in an interactive
	 * login then display them too.
	 */
	if (!check_quietlogin(s, command))
		display_loginmsg();
#endif /* HAVE_OSF_SIA */

#ifdef USE_PAM
	if (options.use_pam && !is_pam_session_open()) {
		debug3("PAM session not opened, exiting");
		display_loginmsg();
		exit(254);
	}
#endif

	/*
	 * Get the shell from the password data.  An empty shell field is
	 * legal, and means /bin/sh.
	 */
	shell = (pw->pw_shell[0] == '\0') ? _PATH_BSHELL : pw->pw_shell;

	/*
	 * Make sure $SHELL points to the shell from the password file,
	 * even if shell is overridden from login.conf
	 */
	env = do_setup_env(ssh, s, shell);

#ifdef HAVE_LOGIN_CAP
	shell = login_getcapstr(lc, "shell", (char *)shell, (char *)shell);
#endif

	/*
	 * Close the connection descriptors; note that this is the child, and
	 * the server will still have the socket open, and it is important
	 * that we do not shutdown it.  Note that the descriptors cannot be
	 * closed before building the environment, as we call
	 * ssh_remote_ipaddr there.
	 */
	child_close_fds(ssh);

	/*
	 * Must take new environment into use so that .ssh/rc,
	 * /etc/ssh/sshrc and xauth are run in the proper environment.
	 */
	environ = env;

#if defined(KRB5) && defined(USE_AFS)
	/*
	 * At this point, we check to see if AFS is active and if we have
	 * a valid Kerberos 5 TGT. If so, it seems like a good idea to see
	 * if we can (and need to) extend the ticket into an AFS token. If
	 * we don't do this, we run into potential problems if the user's
	 * home directory is in AFS and it's not world-readable.
	 */

	if (options.kerberos_get_afs_token && k_hasafs() &&
	    (s->authctxt->krb5_ctx != NULL)) {
		char cell[64];

		debug("Getting AFS token");

		k_setpag();

		if (k_afs_cell_of_file(pw->pw_dir, cell, sizeof(cell)) == 0)
			krb5_afslog(s->authctxt->krb5_ctx,
			    s->authctxt->krb5_fwd_ccache, cell, NULL);

		krb5_afslog_home(s->authctxt->krb5_ctx,
		    s->authctxt->krb5_fwd_ccache, NULL, NULL, pw->pw_dir);
	}
#endif

	/* Change current directory to the user's home directory. */
	if (chdir(pw->pw_dir) < 0) {
		/* Suppress missing homedir warning for chroot case */
#ifdef HAVE_LOGIN_CAP
		r = login_getcapbool(lc, "requirehome", 0);
#endif
		if (r || !in_chroot) {
			fprintf(stderr, "Could not chdir to home "
			    "directory %s: %s\n", pw->pw_dir,
			    strerror(errno));
		}
		if (r)
			exit(1);
	}

	closefrom(STDERR_FILENO + 1);

	do_rc_files(ssh, s, shell);

	/* restore SIGPIPE for child */
	signal(SIGPIPE, SIG_DFL);

	if (s->is_subsystem == SUBSYSTEM_INT_SFTP_ERROR) {
		printf("This service allows sftp connections only.\n");
		fflush(NULL);
		exit(1);
	} else if (s->is_subsystem == SUBSYSTEM_INT_SFTP) {
		extern int optind, optreset;
		int i;
		char *p, *args;

		setproctitle("%s@%s", s->pw->pw_name, INTERNAL_SFTP_NAME);
		args = xstrdup(command ? command : "sftp-server");
		for (i = 0, (p = strtok(args, " ")); p; (p = strtok(NULL, " ")))
			if (i < ARGV_MAX - 1)
				argv[i++] = p;
		argv[i] = NULL;
		optind = optreset = 1;
		__progname = argv[0];
#ifdef WITH_SELINUX
		ssh_selinux_change_context("sftpd_t");
#endif
		exit(sftp_server_main(i, argv, s->pw));
	}

	fflush(NULL);

	/* Get the last component of the shell name. */
	if ((shell0 = strrchr(shell, '/')) != NULL)
		shell0++;
	else
		shell0 = shell;

	/*
	 * If we have no command, execute the shell.  In this case, the shell
	 * name to be passed in argv[0] is preceded by '-' to indicate that
	 * this is a login shell.
	 */
	if (!command) {
		char argv0[256];

		/* Start the shell.  Set initial character to '-'. */
		argv0[0] = '-';

		if (strlcpy(argv0 + 1, shell0, sizeof(argv0) - 1)
		    >= sizeof(argv0) - 1) {
			errno = EINVAL;
			perror(shell);
			exit(1);
		}

		/* Execute the shell. */
		argv[0] = argv0;
		argv[1] = NULL;
		execve(shell, argv, env);

		/* Executing the shell failed. */
		perror(shell);
		exit(1);
	}
	/*
	 * Execute the command using the user's shell.  This uses the -c
	 * option to execute the command.
	 */
	argv[0] = (char *) shell0;
	argv[1] = "-c";
	argv[2] = (char *) command;
	argv[3] = NULL;
	execve(shell, argv, env);
	perror(shell);
	exit(1);
}