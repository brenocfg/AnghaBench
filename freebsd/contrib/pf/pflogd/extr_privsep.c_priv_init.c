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
struct passwd {int /*<<< orphan*/  pw_uid; int /*<<< orphan*/  pw_gid; int /*<<< orphan*/  pw_dir; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_LOCAL ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int NSIG ; 
 int O_APPEND ; 
 int O_CREAT ; 
 int O_NOFOLLOW ; 
 int O_NONBLOCK ; 
 int O_RDWR ; 
 int /*<<< orphan*/  PF_UNSPEC ; 
#define  PRIV_MOVE_LOG 130 
#define  PRIV_OPEN_LOG 129 
#define  PRIV_SET_SNAPLEN 128 
 int SIGALRM ; 
 int SIGCHLD ; 
 int SIGHUP ; 
 int SIGINT ; 
 int SIGQUIT ; 
 int SIGTERM ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int _NSIG ; 
 int /*<<< orphan*/  _exit (int) ; 
 scalar_t__ chdir (char*) ; 
 scalar_t__ child_pid ; 
 scalar_t__ chroot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  endpwent () ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  filename ; 
 scalar_t__ fork () ; 
 struct passwd* getpwnam (char*) ; 
 int /*<<< orphan*/  gotsig_chld ; 
 int /*<<< orphan*/  logmsg (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ may_read (int,int*,int) ; 
 int move_log (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  must_read (int,int*,int) ; 
 int /*<<< orphan*/  must_write (int,int*,int) ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 int priv_fd ; 
 int /*<<< orphan*/  send_fd (int,int) ; 
 int set_snaplen (int) ; 
 int setgroups (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setproctitle (char*) ; 
 int setresgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int setresuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sig_chld ; 
 int /*<<< orphan*/  sig_pass_to_chld ; 
 int /*<<< orphan*/  signal (int,int /*<<< orphan*/ ) ; 
 int socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  strerror (int) ; 

int
priv_init(void)
{
	int i, fd, socks[2], cmd;
	int snaplen, ret, olderrno;
	struct passwd *pw;

#ifdef __FreeBSD__
	for (i = 1; i < NSIG; i++)
#else
	for (i = 1; i < _NSIG; i++)
#endif
		signal(i, SIG_DFL);

	/* Create sockets */
	if (socketpair(AF_LOCAL, SOCK_STREAM, PF_UNSPEC, socks) == -1)
		err(1, "socketpair() failed");

	pw = getpwnam("_pflogd");
	if (pw == NULL)
		errx(1, "unknown user _pflogd");
	endpwent();

	child_pid = fork();
	if (child_pid < 0)
		err(1, "fork() failed");

	if (!child_pid) {
		gid_t gidset[1];

		/* Child - drop privileges and return */
		if (chroot(pw->pw_dir) != 0)
			err(1, "unable to chroot");
		if (chdir("/") != 0)
			err(1, "unable to chdir");

		gidset[0] = pw->pw_gid;
		if (setresgid(pw->pw_gid, pw->pw_gid, pw->pw_gid) == -1)
			err(1, "setresgid() failed");
		if (setgroups(1, gidset) == -1)
			err(1, "setgroups() failed");
		if (setresuid(pw->pw_uid, pw->pw_uid, pw->pw_uid) == -1)
			err(1, "setresuid() failed");
		close(socks[0]);
		priv_fd = socks[1];
		return 0;
	}

	/* Father */
	/* Pass ALRM/TERM/HUP/INT/QUIT through to child, and accept CHLD */
	signal(SIGALRM, sig_pass_to_chld);
	signal(SIGTERM, sig_pass_to_chld);
	signal(SIGHUP,  sig_pass_to_chld);
	signal(SIGINT,  sig_pass_to_chld);
	signal(SIGQUIT,  sig_pass_to_chld);
	signal(SIGCHLD, sig_chld);

	setproctitle("[priv]");
	close(socks[1]);

	while (!gotsig_chld) {
		if (may_read(socks[0], &cmd, sizeof(int)))
			break;
		switch (cmd) {
		case PRIV_SET_SNAPLEN:
			logmsg(LOG_DEBUG,
			    "[priv]: msg PRIV_SET_SNAPLENGTH received");
			must_read(socks[0], &snaplen, sizeof(int));

			ret = set_snaplen(snaplen);
			if (ret) {
				logmsg(LOG_NOTICE,
				   "[priv]: set_snaplen failed for snaplen %d",
				   snaplen);
			}

			must_write(socks[0], &ret, sizeof(int));
			break;

		case PRIV_OPEN_LOG:
			logmsg(LOG_DEBUG,
			    "[priv]: msg PRIV_OPEN_LOG received");
			/* create or append logs but do not follow symlinks */
			fd = open(filename,
			    O_RDWR|O_CREAT|O_APPEND|O_NONBLOCK|O_NOFOLLOW,
			    0600);
			olderrno = errno;
			send_fd(socks[0], fd);
			if (fd < 0)
				logmsg(LOG_NOTICE,
				    "[priv]: failed to open %s: %s",
				    filename, strerror(olderrno));
			else
				close(fd);
			break;

		case PRIV_MOVE_LOG:
			logmsg(LOG_DEBUG,
			    "[priv]: msg PRIV_MOVE_LOG received");
			ret = move_log(filename);
			must_write(socks[0], &ret, sizeof(int));
			break;

		default:
			logmsg(LOG_ERR, "[priv]: unknown command %d", cmd);
			_exit(1);
			/* NOTREACHED */
		}
	}

	_exit(1);
}