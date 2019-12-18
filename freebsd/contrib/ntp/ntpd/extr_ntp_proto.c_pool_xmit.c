#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xpkt ;
struct pkt {int /*<<< orphan*/  xmt; int /*<<< orphan*/  reftime; void* rootdisp; void* rootdelay; int /*<<< orphan*/  refid; int /*<<< orphan*/  precision; int /*<<< orphan*/  ppoll; int /*<<< orphan*/  stratum; int /*<<< orphan*/  li_vn_mode; } ;
struct peer {size_t ttl; int throttle; int minpoll; int /*<<< orphan*/  sent; int /*<<< orphan*/  aorg; int /*<<< orphan*/  hpoll; int /*<<< orphan*/  version; TYPE_1__* ai; int /*<<< orphan*/  hostname; scalar_t__ associd; int /*<<< orphan*/  srcadr; int /*<<< orphan*/ * addrs; } ;
struct interface {int dummy; } ;
struct addrinfo {int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; } ;
typedef  int /*<<< orphan*/  sockaddr_u ;
struct TYPE_5__ {int rflags; } ;
typedef  TYPE_2__ r4addr ;
typedef  int /*<<< orphan*/  l_fp ;
struct TYPE_4__ {struct TYPE_4__* ai_next; scalar_t__ ai_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 int /*<<< orphan*/  DTOFP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DTOUFP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HTONL_FP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* HTONS_FP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  LEN_PKT_NOMAC ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  MODE_CLIENT ; 
 int /*<<< orphan*/  PKT_LI_VN_MODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ POOL_SOLICIT_WINDOW ; 
 int RES_FLAGS ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  STRATUM_TO_PKT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZERO (struct addrinfo) ; 
 scalar_t__ current_time ; 
 struct peer* findexistingpeer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct interface* findinterface (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_systime (int /*<<< orphan*/ *) ; 
 int getaddrinfo_sometime (int /*<<< orphan*/ ,char*,struct addrinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  latoa (struct interface*) ; 
 int /*<<< orphan*/  memset (struct pkt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pool_name_resolved ; 
 int /*<<< orphan*/  restrict_source (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  restrictions (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  sendpkt (int /*<<< orphan*/ *,struct interface*,int /*<<< orphan*/ ,struct pkt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stoa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sys_leap ; 
 int /*<<< orphan*/  sys_precision ; 
 int /*<<< orphan*/  sys_refid ; 
 int /*<<< orphan*/  sys_reftime ; 
 int /*<<< orphan*/  sys_rootdelay ; 
 int /*<<< orphan*/  sys_rootdisp ; 
 int /*<<< orphan*/  sys_stratum ; 
 int /*<<< orphan*/ * sys_ttl ; 
 size_t sys_ttlmax ; 

__attribute__((used)) static void
pool_xmit(
	struct peer *pool	/* pool solicitor association */
	)
{
#ifdef WORKER
	struct pkt		xpkt;	/* transmit packet structure */
	struct addrinfo		hints;
	int			rc;
	struct interface *	lcladr;
	sockaddr_u *		rmtadr;
	r4addr			r4a;
	int			restrict_mask;
	struct peer *		p;
	l_fp			xmt_tx;

	if (NULL == pool->ai) {
		if (pool->addrs != NULL) {
			/* free() is used with copy_addrinfo_list() */
			free(pool->addrs);
			pool->addrs = NULL;
		}
		ZERO(hints);
		hints.ai_family = AF(&pool->srcadr);
		hints.ai_socktype = SOCK_DGRAM;
		hints.ai_protocol = IPPROTO_UDP;
		/* ignore getaddrinfo_sometime() errors, we will retry */
		rc = getaddrinfo_sometime(
			pool->hostname,
			"ntp",
			&hints,
			0,			/* no retry */
			&pool_name_resolved,
			(void *)(intptr_t)pool->associd);
		if (!rc)
			DPRINTF(1, ("pool DNS lookup %s started\n",
				pool->hostname));
		else
			msyslog(LOG_ERR,
				"unable to start pool DNS %s: %m",
				pool->hostname);
		return;
	}

	do {
		/* copy_addrinfo_list ai_addr points to a sockaddr_u */
		rmtadr = (sockaddr_u *)(void *)pool->ai->ai_addr;
		pool->ai = pool->ai->ai_next;
		p = findexistingpeer(rmtadr, NULL, NULL, MODE_CLIENT, 0, NULL);
	} while (p != NULL && pool->ai != NULL);
	if (p != NULL)
		return;	/* out of addresses, re-query DNS next poll */
	restrictions(rmtadr, &r4a);
	restrict_mask = r4a.rflags;
	if (RES_FLAGS & restrict_mask)
		restrict_source(rmtadr, 0,
				current_time + POOL_SOLICIT_WINDOW + 1);
	lcladr = findinterface(rmtadr);
	memset(&xpkt, 0, sizeof(xpkt));
	xpkt.li_vn_mode = PKT_LI_VN_MODE(sys_leap, pool->version,
					 MODE_CLIENT);
	xpkt.stratum = STRATUM_TO_PKT(sys_stratum);
	xpkt.ppoll = pool->hpoll;
	xpkt.precision = sys_precision;
	xpkt.refid = sys_refid;
	xpkt.rootdelay = HTONS_FP(DTOFP(sys_rootdelay));
	xpkt.rootdisp = HTONS_FP(DTOUFP(sys_rootdisp));
	HTONL_FP(&sys_reftime, &xpkt.reftime);
	get_systime(&xmt_tx);
	pool->aorg = xmt_tx;
	HTONL_FP(&xmt_tx, &xpkt.xmt);
	sendpkt(rmtadr, lcladr,
		sys_ttl[(pool->ttl >= sys_ttlmax) ? sys_ttlmax : pool->ttl],
		&xpkt, LEN_PKT_NOMAC);
	pool->sent++;
	pool->throttle += (1 << pool->minpoll) - 2;
	DPRINTF(1, ("pool_xmit: at %ld %s->%s pool\n",
		    current_time, latoa(lcladr), stoa(rmtadr)));
	msyslog(LOG_INFO, "Soliciting pool server %s", stoa(rmtadr));
#endif	/* WORKER */
}