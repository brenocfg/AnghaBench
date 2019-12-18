#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ypstat ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u_char ;
typedef  int /*<<< orphan*/  type ;
struct svc_req {int /*<<< orphan*/  rq_vers; TYPE_1__* rq_xprt; } ;
struct in_addr {int dummy; } ;
struct circleq_dnsentry {int prot_type; char* id; int addrlen; int addrtype; int /*<<< orphan*/  name; int /*<<< orphan*/  addr; int /*<<< orphan*/  type; TYPE_1__* xprt; int /*<<< orphan*/  client_addr; int /*<<< orphan*/  xid; int /*<<< orphan*/ * domain; int /*<<< orphan*/  ypvers; int /*<<< orphan*/  ttl; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  xp_raddr; int /*<<< orphan*/  xp_fd; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  BY_RPC_XID ; 
 int /*<<< orphan*/  DEF_TTL ; 
 int IN6ADDRSZ ; 
 int INADDRSZ ; 
 int MAXHOSTNAMELEN ; 
 int SOCK_DGRAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_TYPE ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct circleq_dnsentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_PTR ; 
 int /*<<< orphan*/  YP_NOKEY ; 
 int /*<<< orphan*/  YP_TRUE ; 
 int /*<<< orphan*/  YP_YPERR ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct circleq_dnsentry*) ; 
 int getsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int inet_aton (char*,struct in_addr*) ; 
 int inet_pton (int,char*,int*) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  pending ; 
 int /*<<< orphan*/  qhead ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  svcudp_get_xid (TYPE_1__*) ; 
 int /*<<< orphan*/  yp_error (char*,...) ; 
 int /*<<< orphan*/ * yp_find_dnsqent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct circleq_dnsentry* yp_malloc_dnsent () ; 
 int /*<<< orphan*/  yp_prune_dnsq () ; 
 char* yp_send_dns_query (char*,int /*<<< orphan*/ ) ; 

ypstat
yp_async_lookup_addr(struct svc_req *rqstp, char *addr, int af)
{
	register struct circleq_dnsentry *q;
	char buf[MAXHOSTNAMELEN], *qp;
	uint32_t abuf[4];	/* IPv4 or IPv6 */
	u_char *uaddr = (u_char *)abuf;
	socklen_t len;
	int type, n;

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

	switch (af) {
	case AF_INET:
		if (inet_aton(addr, (struct in_addr *)uaddr) != 1)
			return(YP_NOKEY);
		snprintf(buf, sizeof(buf), "%u.%u.%u.%u.in-addr.arpa",
		    (uaddr[3] & 0xff), (uaddr[2] & 0xff),
		    (uaddr[1] & 0xff), (uaddr[0] & 0xff));
		len = INADDRSZ;
		break;
	case AF_INET6:
		if (inet_pton(af, addr, uaddr) != 1)
			return(YP_NOKEY);
		qp = buf;
		for (n = IN6ADDRSZ - 1; n >= 0; n--) {
			qp += (size_t)sprintf(qp, "%x.%x.", uaddr[n] & 0xf,
			    (uaddr[n] >> 4) & 0xf);
		}
		strlcat(buf, "ip6.arpa", sizeof(buf));
		len = IN6ADDRSZ;
		break;
	default:
		return(YP_YPERR);
	}

	if ((q = yp_malloc_dnsent()) == NULL)
		return(YP_YPERR);

	if (debug)
		yp_error("DNS address is: %s", buf);

	q->type = T_PTR;
	q->ttl = DEF_TTL;
	q->xprt = rqstp->rq_xprt;
	q->ypvers = rqstp->rq_vers;
	q->domain = NULL;
	q->prot_type = type;
	if (q->prot_type == SOCK_DGRAM)
		q->xid = svcudp_get_xid(q->xprt);
	q->client_addr = q->xprt->xp_raddr;
	q->id = yp_send_dns_query(buf, q->type);

	if (q->id == 0) {
		yp_error("DNS query failed");
		free(q);
		return(YP_YPERR);
	}

	memcpy(q->addr, uaddr, len);
	q->addrlen = len;
	q->addrtype = af;
	q->name = strdup(buf);
	TAILQ_INSERT_HEAD(&qhead, q, links);
	pending++;

	if (debug)
		yp_error("queueing async DNS address lookup (%lu)", q->id);

	yp_prune_dnsq();
	return(YP_TRUE);
}