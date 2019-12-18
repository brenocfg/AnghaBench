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
struct rlimit {scalar_t__ rlim_cur; scalar_t__ rlim_max; } ;
struct config_file {int num_ifs; int outgoing_num_ports; size_t outgoing_num_tcp; int num_threads; scalar_t__ do_ip6; int /*<<< orphan*/  if_automatic; scalar_t__ do_ip4; scalar_t__ incoming_num_tcp; scalar_t__ do_tcp; scalar_t__ do_udp; } ;
typedef  scalar_t__ rlim_t ;

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_NOFILE ; 
 scalar_t__ RLIM_INFINITY ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatal_exit (char*) ; 
 scalar_t__ getrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  log_warn (char*,...) ; 
 scalar_t__ setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ub_event_get_version () ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 

__attribute__((used)) static void
checkrlimits(struct config_file* cfg)
{
#ifndef S_SPLINT_S
#ifdef HAVE_GETRLIMIT
	/* list has number of ports to listen to, ifs number addresses */
	int list = ((cfg->do_udp?1:0) + (cfg->do_tcp?1 + 
			(int)cfg->incoming_num_tcp:0));
	size_t listen_ifs = (size_t)(cfg->num_ifs==0?
		((cfg->do_ip4 && !cfg->if_automatic?1:0) + 
		 (cfg->do_ip6?1:0)):cfg->num_ifs);
	size_t listen_num = list*listen_ifs;
	size_t outudpnum = (size_t)cfg->outgoing_num_ports;
	size_t outtcpnum = cfg->outgoing_num_tcp;
	size_t misc = 4; /* logfile, pidfile, stdout... */
	size_t perthread_noudp = listen_num + outtcpnum + 
		2/*cmdpipe*/ + 2/*libevent*/ + misc; 
	size_t perthread = perthread_noudp + outudpnum;

#if !defined(HAVE_PTHREAD) && !defined(HAVE_SOLARIS_THREADS)
	int numthread = 1; /* it forks */
#else
	int numthread = (cfg->num_threads?cfg->num_threads:1);
#endif
	size_t total = numthread * perthread + misc;
	size_t avail;
	struct rlimit rlim;

	if(total > 1024 && 
		strncmp(ub_event_get_version(), "mini-event", 10) == 0) {
		log_warn("too many file descriptors requested. The builtin"
			"mini-event cannot handle more than 1024. Config "
			"for less fds or compile with libevent");
		if(numthread*perthread_noudp+15 > 1024)
			fatal_exit("too much tcp. not enough fds.");
		cfg->outgoing_num_ports = (int)((1024 
			- numthread*perthread_noudp 
			- 10 /* safety margin */) /numthread);
		log_warn("continuing with less udp ports: %u",
			cfg->outgoing_num_ports);
		total = 1024;
	}
	if(perthread > 64 && 
		strncmp(ub_event_get_version(), "winsock-event", 13) == 0) {
		log_err("too many file descriptors requested. The winsock"
			" event handler cannot handle more than 64 per "
			" thread. Config for less fds");
		if(perthread_noudp+2 > 64)
			fatal_exit("too much tcp. not enough fds.");
		cfg->outgoing_num_ports = (int)((64 
			- perthread_noudp 
			- 2/* safety margin */));
		log_warn("continuing with less udp ports: %u",
			cfg->outgoing_num_ports);
		total = numthread*(perthread_noudp+
			(size_t)cfg->outgoing_num_ports)+misc;
	}
	if(getrlimit(RLIMIT_NOFILE, &rlim) < 0) {
		log_warn("getrlimit: %s", strerror(errno));
		return;
	}
	if(rlim.rlim_cur == (rlim_t)RLIM_INFINITY)
		return;
	if((size_t)rlim.rlim_cur < total) {
		avail = (size_t)rlim.rlim_cur;
		rlim.rlim_cur = (rlim_t)(total + 10);
		rlim.rlim_max = (rlim_t)(total + 10);
#ifdef HAVE_SETRLIMIT
		if(setrlimit(RLIMIT_NOFILE, &rlim) < 0) {
			log_warn("setrlimit: %s", strerror(errno));
#endif
			log_warn("cannot increase max open fds from %u to %u",
				(unsigned)avail, (unsigned)total+10);
			/* check that calculation below does not underflow,
			 * with 15 as margin */
			if(numthread*perthread_noudp+15 > avail)
				fatal_exit("too much tcp. not enough fds.");
			cfg->outgoing_num_ports = (int)((avail 
				- numthread*perthread_noudp 
				- 10 /* safety margin */) /numthread);
			log_warn("continuing with less udp ports: %u",
				cfg->outgoing_num_ports);
			log_warn("increase ulimit or decrease threads, "
				"ports in config to remove this warning");
			return;
#ifdef HAVE_SETRLIMIT
		}
#endif
		verbose(VERB_ALGO, "increased limit(open files) from %u to %u",
			(unsigned)avail, (unsigned)total+10);
	}
#else	
	(void)cfg;
#endif /* HAVE_GETRLIMIT */
#endif /* S_SPLINT_S */
}