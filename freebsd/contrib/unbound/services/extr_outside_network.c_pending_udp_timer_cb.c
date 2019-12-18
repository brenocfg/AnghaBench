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
struct pending {TYPE_1__* pc; TYPE_2__* timer; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  cb_arg; struct outside_network* outnet; } ;
struct outside_network {int /*<<< orphan*/  delay_tv; int /*<<< orphan*/  udp_wait_first; scalar_t__ delayclose; } ;
struct TYPE_4__ {int /*<<< orphan*/ * callback; } ;
struct TYPE_3__ {int /*<<< orphan*/  cp; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETEVENT_TIMEOUT ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  comm_timer_set (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_pending_udp (int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  outnet_send_wait_udp (struct outside_network*) ; 
 int /*<<< orphan*/  pending_delete (struct outside_network*,struct pending*) ; 
 int /*<<< orphan*/  pending_udp_timer_delay_cb ; 
 int /*<<< orphan*/  portcomm_loweruse (struct outside_network*,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

void 
pending_udp_timer_cb(void *arg)
{
	struct pending* p = (struct pending*)arg;
	struct outside_network* outnet = p->outnet;
	/* it timed out */
	verbose(VERB_ALGO, "timeout udp");
	if(p->cb) {
		fptr_ok(fptr_whitelist_pending_udp(p->cb));
		(void)(*p->cb)(p->pc->cp, p->cb_arg, NETEVENT_TIMEOUT, NULL);
	}
	/* if delayclose, keep port open for a longer time.
	 * But if the udpwaitlist exists, then we are struggling to
	 * keep up with demand for sockets, so do not wait, but service
	 * the customer (customer service more important than portICMPs) */
	if(outnet->delayclose && !outnet->udp_wait_first) {
		p->cb = NULL;
		p->timer->callback = &pending_udp_timer_delay_cb;
		comm_timer_set(p->timer, &outnet->delay_tv);
		return;
	}
	portcomm_loweruse(outnet, p->pc);
	pending_delete(outnet, p);
	outnet_send_wait_udp(outnet);
}