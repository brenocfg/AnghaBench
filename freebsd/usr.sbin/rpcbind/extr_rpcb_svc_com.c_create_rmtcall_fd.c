#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct t_bind {int dummy; } ;
struct rmtcallfd_list {int fd; struct rmtcallfd_list* next; int /*<<< orphan*/  netid; TYPE_1__* xprt; } ;
struct netconfig {char* nc_device; int /*<<< orphan*/  nc_netid; } ;
struct TYPE_3__ {int /*<<< orphan*/  xp_netid; } ;
typedef  TYPE_1__ SVCXPRT ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int __rpc_nconf2fd (struct netconfig*) ; 
 scalar_t__ debugging ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 struct rmtcallfd_list* malloc (int) ; 
 struct rmtcallfd_list* rmthead ; 
 struct rmtcallfd_list* rmttail ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_fdset ; 
 int svc_maxfd ; 
 TYPE_1__* svc_tli_create (int,int /*<<< orphan*/ ,struct t_bind*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

int
create_rmtcall_fd(struct netconfig *nconf)
{
	int fd;
	struct rmtcallfd_list *rmt;
	SVCXPRT *xprt;

	if ((fd = __rpc_nconf2fd(nconf)) == -1) {
		if (debugging)
			fprintf(stderr,
	"create_rmtcall_fd: couldn't open \"%s\" (errno %d)\n",
			nconf->nc_device, errno);
		return (-1);
	}
	xprt = svc_tli_create(fd, 0, (struct t_bind *) 0, 0, 0);
	if (xprt == NULL) {
		if (debugging)
			fprintf(stderr,
				"create_rmtcall_fd: svc_tli_create failed\n");
		return (-1);
	}
	rmt = malloc(sizeof (struct rmtcallfd_list));
	if (rmt == NULL) {
		syslog(LOG_ERR, "create_rmtcall_fd: no memory!");
		return (-1);
	}
	rmt->xprt = xprt;
	rmt->netid = strdup(nconf->nc_netid);
	xprt->xp_netid = rmt->netid;
	rmt->fd = fd;
	rmt->next = NULL;
	if (rmthead == NULL) {
		rmthead = rmt;
		rmttail = rmt;
	} else {
		rmttail->next = rmt;
		rmttail = rmt;
	}
	/* XXX not threadsafe */
	if (fd > svc_maxfd)
		svc_maxfd = fd;
	FD_SET(fd, &svc_fdset);
	return (fd);
}