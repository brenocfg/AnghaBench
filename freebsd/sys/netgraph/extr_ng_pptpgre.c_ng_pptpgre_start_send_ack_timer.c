#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* hpriv_p ;
struct TYPE_4__ {int rtt; int /*<<< orphan*/  hook; int /*<<< orphan*/  node; int /*<<< orphan*/  sackTimer; } ;

/* Variables and functions */
 int PPTP_MAX_ACK_DELAY ; 
 int PPTP_MIN_ACK_DELAY ; 
 int /*<<< orphan*/  PPTP_TIME_SCALE ; 
 int howmany (int,int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  ng_callout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_pptpgre_send_ack_timeout ; 

__attribute__((used)) static void
ng_pptpgre_start_send_ack_timer(hpriv_p hpriv)
{
	int ackTimeout, ticks;

	/* Take 1/4 of the estimated round trip time */
	ackTimeout = (hpriv->rtt >> 2);
	if (ackTimeout < PPTP_MIN_ACK_DELAY)
		ackTimeout = PPTP_MIN_ACK_DELAY;
	else if (ackTimeout > PPTP_MAX_ACK_DELAY)
		ackTimeout = PPTP_MAX_ACK_DELAY;

	/* Be conservative: timeout can happen up to 1 tick early */
	ticks = howmany(ackTimeout * hz, PPTP_TIME_SCALE);
	ng_callout(&hpriv->sackTimer, hpriv->node, hpriv->hook,
	    ticks, ng_pptpgre_send_ack_timeout, hpriv, 0);
}