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
struct passwd {int /*<<< orphan*/  pw_uid; int /*<<< orphan*/  pw_gid; } ;
struct event {int dummy; } ;
struct env {TYPE_2__* sc_iev; } ;
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_3__ {int /*<<< orphan*/  fd; } ;
struct TYPE_4__ {int /*<<< orphan*/  ev; int /*<<< orphan*/  handler; int /*<<< orphan*/  events; TYPE_1__ ibuf; struct env* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dns_dispatch_imsg ; 
 int /*<<< orphan*/  dns_shutdown () ; 
 int /*<<< orphan*/  dns_sig_handler ; 
 int /*<<< orphan*/  endservent () ; 
 int /*<<< orphan*/  event_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_dispatch () ; 
 int /*<<< orphan*/  event_init () ; 
 int /*<<< orphan*/  event_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct env*) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  fork () ; 
 int /*<<< orphan*/  imsg_init (TYPE_1__*,int) ; 
 scalar_t__ setgroups (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setproctitle (char*) ; 
 scalar_t__ setresgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ setresuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_add (struct event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_set (struct event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

pid_t
ypldap_dns(int pipe_ntp[2], struct passwd *pw)
{
	pid_t			 pid;
	struct event	 ev_sigint;
	struct event	 ev_sigterm;
	struct event	 ev_sighup;
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

	setproctitle("dns engine");
	close(pipe_ntp[0]);

	if (setgroups(1, &pw->pw_gid) ||
	    setresgid(pw->pw_gid, pw->pw_gid, pw->pw_gid) ||
	    setresuid(pw->pw_uid, pw->pw_uid, pw->pw_uid))
		fatal("can't drop privileges");
	endservent();

	event_init();
	signal_set(&ev_sigint, SIGINT, dns_sig_handler, NULL);
	signal_set(&ev_sigterm, SIGTERM, dns_sig_handler, NULL);
	signal_set(&ev_sighup, SIGHUP, dns_sig_handler, NULL);
	signal_add(&ev_sigint, NULL);
	signal_add(&ev_sigterm, NULL);
	signal_add(&ev_sighup, NULL);

	if ((env.sc_iev = calloc(1, sizeof(*env.sc_iev))) == NULL)
		fatal(NULL);

	env.sc_iev->events = EV_READ;
	env.sc_iev->data = &env;
	imsg_init(&env.sc_iev->ibuf, pipe_ntp[1]);
	env.sc_iev->handler = dns_dispatch_imsg;
	event_set(&env.sc_iev->ev, env.sc_iev->ibuf.fd, env.sc_iev->events,
	    env.sc_iev->handler, &env);
	event_add(&env.sc_iev->ev, NULL);

	event_dispatch();
	dns_shutdown();

	return (0);
}