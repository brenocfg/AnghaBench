#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pending {int /*<<< orphan*/  pc; struct outside_network* outnet; } ;
struct outside_network {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  outnet_send_wait_udp (struct outside_network*) ; 
 int /*<<< orphan*/  pending_delete (struct outside_network*,struct pending*) ; 
 int /*<<< orphan*/  portcomm_loweruse (struct outside_network*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

void
pending_udp_timer_delay_cb(void* arg)
{
	struct pending* p = (struct pending*)arg;
	struct outside_network* outnet = p->outnet;
	verbose(VERB_ALGO, "timeout udp with delay");
	portcomm_loweruse(outnet, p->pc);
	pending_delete(outnet, p);
	outnet_send_wait_udp(outnet);
}