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
typedef  int /*<<< orphan*/  u_short ;
typedef  int /*<<< orphan*/  throughput ;
struct servent {scalar_t__ s_port; } ;
struct passwd {char* pw_name; } ;
typedef  int /*<<< orphan*/  size ;
typedef  int /*<<< orphan*/  on ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int IPTOS_THROUGHPUT ; 
 int /*<<< orphan*/  IP_TOS ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVBUF ; 
 int /*<<< orphan*/  SO_SNDBUF ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int TP_BSIZE ; 
 int /*<<< orphan*/  X_STARTUP ; 
 char* _PATH_RMT ; 
 int /*<<< orphan*/  errfd ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* getenv (char*) ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 struct servent* getservbyname (char*,char*) ; 
 int /*<<< orphan*/  getuid () ; 
 int /*<<< orphan*/  msg (char*,...) ; 
 int ntrec ; 
 int /*<<< orphan*/  okname (char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ rcmd (char**,int /*<<< orphan*/ ,char*,char*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ rmtape ; 
 char* rmtpeer ; 
 scalar_t__ setsockopt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 

void
rmtgetconn(void)
{
	char *cp;
	const char *rmt;
	static struct servent *sp = NULL;
	static struct passwd *pwd = NULL;
	char *tuser;
	int size;
	int throughput;
	int on;

	if (sp == NULL) {
		sp = getservbyname("shell", "tcp");
		if (sp == NULL) {
			msg("shell/tcp: unknown service\n");
			exit(X_STARTUP);
		}
		pwd = getpwuid(getuid());
		if (pwd == NULL) {
			msg("who are you?\n");
			exit(X_STARTUP);
		}
	}
	if ((cp = strchr(rmtpeer, '@')) != NULL) {
		tuser = rmtpeer;
		*cp = '\0';
		if (!okname(tuser))
			exit(X_STARTUP);
		rmtpeer = ++cp;
	} else
		tuser = pwd->pw_name;
	if ((rmt = getenv("RMT")) == NULL)
		rmt = _PATH_RMT;
	msg("%s", "");
	rmtape = rcmd(&rmtpeer, (u_short)sp->s_port, pwd->pw_name,
		      tuser, rmt, &errfd);
	if (rmtape < 0) {
		msg("login to %s as %s failed.\n", rmtpeer, tuser);
		return;
	}
	(void)fprintf(stderr, "Connection to %s established.\n", rmtpeer);
	size = ntrec * TP_BSIZE;
	if (size > 60 * 1024)		/* XXX */
		size = 60 * 1024;
	/* Leave some space for rmt request/response protocol */
	size += 2 * 1024;
	while (size > TP_BSIZE &&
	    setsockopt(rmtape, SOL_SOCKET, SO_SNDBUF, &size, sizeof (size)) < 0)
		    size -= TP_BSIZE;
	(void)setsockopt(rmtape, SOL_SOCKET, SO_RCVBUF, &size, sizeof (size));
	throughput = IPTOS_THROUGHPUT;
	if (setsockopt(rmtape, IPPROTO_IP, IP_TOS,
	    &throughput, sizeof(throughput)) < 0)
		perror("IP_TOS:IPTOS_THROUGHPUT setsockopt");
	on = 1;
	if (setsockopt(rmtape, IPPROTO_TCP, TCP_NODELAY, &on, sizeof (on)) < 0)
		perror("TCP_NODELAY setsockopt");
}