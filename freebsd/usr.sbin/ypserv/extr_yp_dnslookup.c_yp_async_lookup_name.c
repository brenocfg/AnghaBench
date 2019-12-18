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
typedef  int /*<<< orphan*/  ypstat ;
typedef  int /*<<< orphan*/  type ;
struct svc_req {int /*<<< orphan*/  rq_vers; TYPE_1__* rq_xprt; } ;
struct circleq_dnsentry {int prot_type; scalar_t__ id; int /*<<< orphan*/  name; int /*<<< orphan*/  type; int /*<<< orphan*/  domain; TYPE_1__* xprt; int /*<<< orphan*/  client_addr; int /*<<< orphan*/  xid; int /*<<< orphan*/  ypvers; int /*<<< orphan*/  ttl; } ;
typedef  int socklen_t ;
struct TYPE_4__ {int /*<<< orphan*/  dnsrch; } ;
struct TYPE_3__ {int /*<<< orphan*/  xp_raddr; int /*<<< orphan*/  xp_fd; } ;

/* Variables and functions */
 int AF_INET ; 
 int /*<<< orphan*/  BY_RPC_XID ; 
 int /*<<< orphan*/  DEF_TTL ; 
 int SOCK_DGRAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_TYPE ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct circleq_dnsentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_A ; 
 int /*<<< orphan*/  T_AAAA ; 
 int /*<<< orphan*/  YP_TRUE ; 
 int /*<<< orphan*/  YP_YPERR ; 
 TYPE_2__ _res ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct circleq_dnsentry*) ; 
 int getsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  pending ; 
 int /*<<< orphan*/  qhead ; 
 int /*<<< orphan*/  strdup (char*) ; 
 scalar_t__ strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svcudp_get_xid (TYPE_1__*) ; 
 int /*<<< orphan*/  yp_error (char*,...) ; 
 int /*<<< orphan*/ * yp_find_dnsqent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct circleq_dnsentry* yp_malloc_dnsent () ; 
 int /*<<< orphan*/  yp_prune_dnsq () ; 
 scalar_t__ yp_send_dns_query (char*,int /*<<< orphan*/ ) ; 

ypstat
yp_async_lookup_name(struct svc_req *rqstp, char *name, int af)
{
	register struct circleq_dnsentry *q;
	socklen_t len;
	int type;

	/* Check for SOCK_DGRAM or SOCK_STREAM -- we need to know later */
	type = -1;
	len = sizeof(type);
	if (getsockopt(rqstp->rq_xprt->xp_fd, SOL_SOCKET,
					SO_TYPE, &type, &len) == -1) {
		yp_error("getsockopt failed: %s", strerror(errno));
		return(YP_YPERR);
	}

	/* Avoid transmitting dupe requests. */
	if (type == SOCK_DGRAM &&
	    yp_find_dnsqent(svcudp_get_xid(rqstp->rq_xprt),BY_RPC_XID) != NULL)
		return(YP_TRUE);

	if ((q = yp_malloc_dnsent()) == NULL)
		return(YP_YPERR);

	q->type = (af == AF_INET) ? T_A : T_AAAA;
	q->ttl = DEF_TTL;
	q->xprt = rqstp->rq_xprt;
	q->ypvers = rqstp->rq_vers;
	q->prot_type = type;
	if (q->prot_type == SOCK_DGRAM)
		q->xid = svcudp_get_xid(q->xprt);
	q->client_addr = q->xprt->xp_raddr;
	q->domain = _res.dnsrch;
	q->id = yp_send_dns_query(name, q->type);

	if (q->id == 0) {
		yp_error("DNS query failed");
		free(q);
		return(YP_YPERR);
	}

	q->name = strdup(name);
	TAILQ_INSERT_HEAD(&qhead, q, links);
	pending++;

	if (debug)
		yp_error("queueing async DNS name lookup (%lu)", q->id);

	yp_prune_dnsq();
	return(YP_TRUE);
}