#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct passwd {int /*<<< orphan*/  pw_uid; int /*<<< orphan*/  pw_gid; int /*<<< orphan*/  pw_dir; } ;
struct event {int dummy; } ;
struct env {TYPE_2__* sc_iev_dns; TYPE_1__* sc_iev; int /*<<< orphan*/  sc_idms; } ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  env ;
struct TYPE_6__ {int /*<<< orphan*/  fd; } ;
struct TYPE_5__ {int /*<<< orphan*/  ev; int /*<<< orphan*/  handler; void* events; TYPE_3__ ibuf; struct env* data; } ;
struct TYPE_4__ {int /*<<< orphan*/  ev; int /*<<< orphan*/  handler; void* events; TYPE_3__ ibuf; struct env* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 void* EV_READ ; 
 int /*<<< orphan*/  PF_UNSPEC ; 
 int /*<<< orphan*/  PROC_CLIENT ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  YPLDAP_USER ; 
 void* calloc (int,int) ; 
 int chdir (char*) ; 
 int chroot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  client_dispatch_dns ; 
 int /*<<< orphan*/  client_dispatch_parent ; 
 int /*<<< orphan*/  client_shutdown () ; 
 int /*<<< orphan*/  client_sig_handler ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  event_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_dispatch () ; 
 int /*<<< orphan*/  event_init () ; 
 int /*<<< orphan*/  event_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,struct env*) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  fork () ; 
 struct passwd* getpwnam (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imsg_init (TYPE_3__*,int) ; 
 int /*<<< orphan*/  memset (struct env*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ setgroups (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setproctitle (char*) ; 
 scalar_t__ setresgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ setresuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_add (struct event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_set (struct event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ypldap_dns (int*,struct passwd*) ; 
 int /*<<< orphan*/  ypldap_process ; 

pid_t
ldapclient(int pipe_main2client[2])
{
	pid_t            pid, dns_pid;
	int              pipe_dns[2];
	struct passwd	*pw;
	struct event	 ev_sigint;
	struct event	 ev_sigterm;
	struct env	 env;

	switch (pid = fork()) {
	case -1:
		fatal("cannot fork");
		break;
	case 0:
		break;
	default:
		return (pid);
	}

	memset(&env, 0, sizeof(env));
	TAILQ_INIT(&env.sc_idms);

	if ((pw = getpwnam(YPLDAP_USER)) == NULL)
		fatal("getpwnam");

	if (socketpair(AF_UNIX, SOCK_STREAM, PF_UNSPEC, pipe_dns) == -1)
		fatal("socketpair");
	dns_pid = ypldap_dns(pipe_dns, pw);
	close(pipe_dns[1]);

#ifndef DEBUG
	if (chroot(pw->pw_dir) == -1)
		fatal("chroot");
	if (chdir("/") == -1)
		fatal("chdir");
#else
#warning disabling chrooting in DEBUG mode
#endif
	setproctitle("ldap client");
	ypldap_process = PROC_CLIENT;

#ifndef DEBUG
	if (setgroups(1, &pw->pw_gid) ||
	    setresgid(pw->pw_gid, pw->pw_gid, pw->pw_gid) ||
	    setresuid(pw->pw_uid, pw->pw_uid, pw->pw_uid))
		fatal("cannot drop privileges");
#else
#warning disabling privilege revocation in DEBUG mode
#endif

	event_init();
	signal(SIGPIPE, SIG_IGN);
	signal_set(&ev_sigint, SIGINT, client_sig_handler, NULL);
	signal_set(&ev_sigterm, SIGTERM, client_sig_handler, NULL);
	signal_add(&ev_sigint, NULL);
	signal_add(&ev_sigterm, NULL);

	close(pipe_main2client[0]);
	if ((env.sc_iev = calloc(1, sizeof(*env.sc_iev))) == NULL)
		fatal(NULL);
	if ((env.sc_iev_dns = calloc(1, sizeof(*env.sc_iev_dns))) == NULL)
		fatal(NULL);

	env.sc_iev->events = EV_READ;
	env.sc_iev->data = &env;
	imsg_init(&env.sc_iev->ibuf, pipe_main2client[1]);
	env.sc_iev->handler = client_dispatch_parent;
	event_set(&env.sc_iev->ev, env.sc_iev->ibuf.fd, env.sc_iev->events,
	    env.sc_iev->handler, &env);
	event_add(&env.sc_iev->ev, NULL);

	env.sc_iev_dns->events = EV_READ;
	env.sc_iev_dns->data = &env;
	imsg_init(&env.sc_iev_dns->ibuf, pipe_dns[0]);
	env.sc_iev_dns->handler = client_dispatch_dns;
	event_set(&env.sc_iev_dns->ev, env.sc_iev_dns->ibuf.fd,
	    env.sc_iev_dns->events, env.sc_iev_dns->handler, &env);
	event_add(&env.sc_iev_dns->ev, NULL);

	event_dispatch();
	client_shutdown();

	return (0);

}