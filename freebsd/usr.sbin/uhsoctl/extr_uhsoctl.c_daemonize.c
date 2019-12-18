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
struct pidfh {int dummy; } ;
struct ctx {char* ifnam; int /*<<< orphan*/  flags; struct pidfh* pfh; int /*<<< orphan*/  pidfile; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_DAEMON ; 
 int /*<<< orphan*/  LOG_PID ; 
 int /*<<< orphan*/  LOG_USER ; 
 char* PIDFILE ; 
 int daemon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* getprogname () ; 
 int /*<<< orphan*/  openlog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pidfh* pidfile_open (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pidfile_remove (struct pidfh*) ; 
 int /*<<< orphan*/  pidfile_write (struct pidfh*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,...) ; 
 int syslog_open ; 
 int /*<<< orphan*/  syslog_title ; 
 int /*<<< orphan*/  warn (char*,...) ; 

__attribute__((used)) static void
daemonize(struct ctx *ctx)
{
	struct pidfh *pfh;
	pid_t opid;

	snprintf(ctx->pidfile, 127, PIDFILE, ctx->ifnam);

	pfh = pidfile_open(ctx->pidfile, 0600, &opid);
	if (pfh == NULL) {
		warn("Cannot create pidfile %s", ctx->pidfile);
		return;
	}

	if (daemon(0, 0) == -1) {
		warn("Cannot daemonize");
		pidfile_remove(pfh);
		return;
	}
	
	pidfile_write(pfh);
	ctx->pfh = pfh;
	ctx->flags |= FLG_DAEMON;

	snprintf(syslog_title, 63, "%s:%s", getprogname(), ctx->ifnam);
	openlog(syslog_title, LOG_PID, LOG_USER);
	syslog_open = 1;
}