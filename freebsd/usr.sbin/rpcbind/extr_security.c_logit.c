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
struct sockaddr {scalar_t__ sa_family; int /*<<< orphan*/  sa_len; } ;
struct rpcent {char* r_name; } ;
typedef  scalar_t__ rpcprog_t ;
typedef  int rpcproc_t ;
typedef  int /*<<< orphan*/  progbuf ;

/* Variables and functions */
 scalar_t__ AF_LOCAL ; 
 int NI_MAXHOST ; 
 int /*<<< orphan*/  NI_NUMERICHOST ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  getnameinfo (struct sockaddr*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rpcent* getrpcbynumber (int) ; 
 int /*<<< orphan*/  setproctitle (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  syslog (int,char*,char*,char const*,char*,char const*) ; 

void
logit(int severity, struct sockaddr *addr, rpcproc_t procnum, rpcprog_t prognum,
      const char *text)
{
	const char *procname;
	char	procbuf[32];
	char   *progname;
	char	progbuf[32];
	char fromname[NI_MAXHOST];
	struct rpcent *rpc;
	static const char *procmap[] = {
	/* RPCBPROC_NULL */		"null",
	/* RPCBPROC_SET */		"set",
	/* RPCBPROC_UNSET */		"unset",
	/* RPCBPROC_GETADDR */		"getport/addr",
	/* RPCBPROC_DUMP */		"dump",
	/* RPCBPROC_CALLIT */		"callit",
	/* RPCBPROC_GETTIME */		"gettime",
	/* RPCBPROC_UADDR2TADDR */	"uaddr2taddr",
	/* RPCBPROC_TADDR2UADDR */	"taddr2uaddr",
	/* RPCBPROC_GETVERSADDR */	"getversaddr",
	/* RPCBPROC_INDIRECT */		"indirect",
	/* RPCBPROC_GETADDRLIST */	"getaddrlist",
	/* RPCBPROC_GETSTAT */		"getstat"
	};
   
	/*
	 * Fork off a process or the portmap daemon might hang while
	 * getrpcbynumber() or syslog() does its thing.
	 */

	if (fork() == 0) {
		setproctitle("logit");

		/* Try to map program number to name. */

		if (prognum == 0) {
			progname = "";
		} else if ((rpc = getrpcbynumber((int) prognum))) {
			progname = rpc->r_name;
		} else {
			snprintf(progname = progbuf, sizeof(progbuf), "%u",
			    (unsigned)prognum);
		}

		/* Try to map procedure number to name. */

		if (procnum >= (sizeof procmap / sizeof (char *))) {
			snprintf(procbuf, sizeof procbuf, "%u",
			    (unsigned)procnum);
			procname = procbuf;
		} else
			procname = procmap[procnum];

		/* Write syslog record. */

		if (addr->sa_family == AF_LOCAL)
			strcpy(fromname, "local");
		else
			getnameinfo(addr, addr->sa_len, fromname,
			    sizeof fromname, NULL, 0, NI_NUMERICHOST);

		syslog(severity, "connect from %s to %s(%s)%s",
			fromname, procname, progname, text);
		_exit(0);
	}
}