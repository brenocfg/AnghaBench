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
struct TYPE_4__ {TYPE_2__* spkt; int /*<<< orphan*/  sock; } ;
typedef  TYPE_1__ xmt_ctx ;
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  u_int ;
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct pkt {int dummy; } ;
struct dns_ctx {int /*<<< orphan*/  name; int /*<<< orphan*/  key; int /*<<< orphan*/  key_id; } ;
typedef  int /*<<< orphan*/  sockaddr_u ;
struct TYPE_5__ {scalar_t__ stime; int /*<<< orphan*/  x_pkt; int /*<<< orphan*/  addr; struct dns_ctx* dctx; } ;
typedef  TYPE_2__ sent_pkt ;
typedef  int /*<<< orphan*/  SOCKET ;

/* Variables and functions */
 scalar_t__ JAN_1970 ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  TRACE (int,char*) ; 
 int /*<<< orphan*/  dec_pending_ntp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 size_t generate_pkt (struct pkt*,struct timeval*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct pkt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,size_t) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*) ; 
 int sendpkt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pkt*,size_t) ; 
 int /*<<< orphan*/  stoa (int /*<<< orphan*/ *) ; 

void
xmt(
	xmt_ctx *	xctx
	)
{
	SOCKET		sock = xctx->sock;
	struct dns_ctx *dctx = xctx->spkt->dctx;
	sent_pkt *	spkt = xctx->spkt;
	sockaddr_u *	dst = &spkt->addr;
	struct timeval	tv_xmt;
	struct pkt	x_pkt;
	size_t		pkt_len;
	int		sent;

	if (0 != gettimeofday(&tv_xmt, NULL)) {
		msyslog(LOG_ERR,
			"xmt: gettimeofday() failed: %m");
		exit(1);
	}
	tv_xmt.tv_sec += JAN_1970;

	pkt_len = generate_pkt(&x_pkt, &tv_xmt, dctx->key_id,
			       dctx->key);

	sent = sendpkt(sock, dst, &x_pkt, pkt_len);
	if (sent) {
		/* Save the packet we sent... */
		memcpy(&spkt->x_pkt, &x_pkt, min(sizeof(spkt->x_pkt),
		       pkt_len));
		spkt->stime = tv_xmt.tv_sec - JAN_1970;

		TRACE(2, ("xmt: %lx.%6.6u %s %s\n", (u_long)tv_xmt.tv_sec,
			  (u_int)tv_xmt.tv_usec, dctx->name, stoa(dst)));
	} else {
		dec_pending_ntp(dctx->name, dst);
	}

	return;
}