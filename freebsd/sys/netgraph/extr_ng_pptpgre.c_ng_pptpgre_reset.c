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
struct ng_pptpgre_roq {int /*<<< orphan*/  item; } ;
typedef  TYPE_2__* hpriv_p ;
struct TYPE_4__ {int peerPpd; int recvWin; } ;
struct TYPE_5__ {int rtt; int xmitWin; int winAck; scalar_t__ roq_len; int /*<<< orphan*/  roq; int /*<<< orphan*/  node; int /*<<< orphan*/  reorderTimer; int /*<<< orphan*/  rackTimer; int /*<<< orphan*/  sackTimer; int /*<<< orphan*/  xmitAck; int /*<<< orphan*/  xmitSeq; int /*<<< orphan*/  recvAck; int /*<<< orphan*/  recvSeq; TYPE_1__ conf; scalar_t__ dev; int /*<<< orphan*/  ato; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NETGRAPH ; 
 int /*<<< orphan*/  NG_FREE_ITEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPTP_MAX_TIMEOUT ; 
 int PPTP_TIME_SCALE ; 
 int PPTP_XMIT_WIN ; 
 int /*<<< orphan*/  SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 struct ng_pptpgre_roq* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ng_pptpgre_roq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  ng_uncallout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ng_pptpgre_reset(hpriv_p hpriv)
{
	struct ng_pptpgre_roq *np;

	/* Reset adaptive timeout state */
	hpriv->ato = PPTP_MAX_TIMEOUT;
	hpriv->rtt = PPTP_TIME_SCALE / 10;
	if (hpriv->conf.peerPpd > 1)	/* ppd = 0 treat as = 1 */
		hpriv->rtt *= hpriv->conf.peerPpd;
	hpriv->dev = 0;
	hpriv->xmitWin = (hpriv->conf.recvWin + 1) / 2;
	if (hpriv->xmitWin < 2)		/* often the first packet is lost */
		hpriv->xmitWin = 2;		/*   because the peer isn't ready */
	else if (hpriv->xmitWin > PPTP_XMIT_WIN)
		hpriv->xmitWin = PPTP_XMIT_WIN;
	hpriv->winAck = hpriv->xmitWin;

	/* Reset sequence numbers */
	hpriv->recvSeq = ~0;
	hpriv->recvAck = ~0;
	hpriv->xmitSeq = ~0;
	hpriv->xmitAck = ~0;

	/* Stop timers */
	ng_uncallout(&hpriv->sackTimer, hpriv->node);
	ng_uncallout(&hpriv->rackTimer, hpriv->node);
	ng_uncallout(&hpriv->reorderTimer, hpriv->node);

	/* Clear reorder queue */
	while (!SLIST_EMPTY(&hpriv->roq)) {
		np = SLIST_FIRST(&hpriv->roq);
		SLIST_REMOVE_HEAD(&hpriv->roq, next);
		NG_FREE_ITEM(np->item);
		free(np, M_NETGRAPH);
	}
	hpriv->roq_len = 0;
}