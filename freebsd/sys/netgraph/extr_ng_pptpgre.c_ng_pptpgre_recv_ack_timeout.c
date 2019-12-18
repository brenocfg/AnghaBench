#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  TYPE_3__* hpriv_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_7__ {scalar_t__ rtt; scalar_t__ ato; int xmitWin; scalar_t__ recvAck; scalar_t__ winAck; scalar_t__ xmitSeq; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  recvAckTimeouts; } ;
struct TYPE_6__ {TYPE_1__ stats; } ;

/* Variables and functions */
 TYPE_2__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 scalar_t__ PPTP_ACK_CHI (int /*<<< orphan*/ ) ; 
 scalar_t__ PPTP_ACK_DELTA (scalar_t__) ; 
 scalar_t__ PPTP_MAX_TIMEOUT ; 
 scalar_t__ PPTP_MIN_TIMEOUT ; 

__attribute__((used)) static void
ng_pptpgre_recv_ack_timeout(node_p node, hook_p hook, void *arg1, int arg2)
{
	const priv_p priv = NG_NODE_PRIVATE(node);
	const hpriv_p hpriv = arg1;

	/* Update adaptive timeout stuff */
	priv->stats.recvAckTimeouts++;
	hpriv->rtt = PPTP_ACK_DELTA(hpriv->rtt) + 1; /* +1 to avoid delta*0 case */
	hpriv->ato = hpriv->rtt + PPTP_ACK_CHI(hpriv->dev);
	if (hpriv->ato > PPTP_MAX_TIMEOUT)
		hpriv->ato = PPTP_MAX_TIMEOUT;
	else if (hpriv->ato < PPTP_MIN_TIMEOUT)
		hpriv->ato = PPTP_MIN_TIMEOUT;

	/* Reset ack and sliding window */
	hpriv->recvAck = hpriv->xmitSeq;		/* pretend we got the ack */
	hpriv->xmitWin = (hpriv->xmitWin + 1) / 2;	/* shrink transmit window */
	hpriv->winAck = hpriv->recvAck + hpriv->xmitWin;	/* reset win expand time */
}