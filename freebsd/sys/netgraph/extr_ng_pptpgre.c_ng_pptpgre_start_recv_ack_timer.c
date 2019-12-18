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
struct TYPE_4__ {int* timeSent; int ato; int /*<<< orphan*/  hook; int /*<<< orphan*/  node; int /*<<< orphan*/  rackTimer; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPTP_TIME_SCALE ; 
 int howmany (int,int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  ng_callout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_pptpgre_recv_ack_timeout ; 
 int ng_pptpgre_time () ; 

__attribute__((used)) static void
ng_pptpgre_start_recv_ack_timer(hpriv_p hpriv)
{
	int remain, ticks;

	/* Compute how long until oldest unack'd packet times out,
	   and reset the timer to that time. */
	remain = (hpriv->timeSent[0] + hpriv->ato) - ng_pptpgre_time();
	if (remain < 0)
		remain = 0;

	/* Be conservative: timeout can happen up to 1 tick early */
	ticks = howmany(remain * hz, PPTP_TIME_SCALE) + 1;
	ng_callout(&hpriv->rackTimer, hpriv->node, hpriv->hook,
	    ticks, ng_pptpgre_recv_ack_timeout, hpriv, 0);
}