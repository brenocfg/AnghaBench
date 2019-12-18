#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* hpriv_p ;
struct TYPE_6__ {int /*<<< orphan*/  enableDelayedAck; } ;
struct TYPE_7__ {int /*<<< orphan*/  mtx; TYPE_1__ conf; int /*<<< orphan*/  sackTimer; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  callout_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_pptpgre_start_send_ack_timer (TYPE_2__* const) ; 
 int /*<<< orphan*/  ng_pptpgre_xmit (TYPE_2__* const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ng_pptpgre_ack(const hpriv_p hpriv)
{
	mtx_assert(&hpriv->mtx, MA_OWNED);
	if (!(callout_pending(&hpriv->sackTimer))) {
		/* If delayed ACK is disabled, send it now */
		if (!hpriv->conf.enableDelayedAck) {	/* ack now */
			ng_pptpgre_xmit(hpriv, NULL);
			/* ng_pptpgre_xmit() drops the mutex */
			return;
		}
		/* ack later */
		ng_pptpgre_start_send_ack_timer(hpriv);
		mtx_unlock(&hpriv->mtx);
		return;
	}
	mtx_unlock(&hpriv->mtx);
}