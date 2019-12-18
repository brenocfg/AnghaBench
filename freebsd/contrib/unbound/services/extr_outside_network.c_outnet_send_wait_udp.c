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
struct pending {int /*<<< orphan*/  cb_arg; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  timeout; scalar_t__ pkt_len; int /*<<< orphan*/ * pkt; struct pending* next_waiting; } ;
struct outside_network {TYPE_1__* unused_fds; int /*<<< orphan*/  udp_buff; int /*<<< orphan*/ * udp_wait_last; struct pending* udp_wait_first; int /*<<< orphan*/  want_to_quit; } ;
struct TYPE_2__ {int /*<<< orphan*/  cp; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETEVENT_CLOSED ; 
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_pending_udp (int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pending_delete (struct outside_network*,struct pending*) ; 
 int /*<<< orphan*/  randomize_and_send_udp (struct pending*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_flip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
outnet_send_wait_udp(struct outside_network* outnet)
{
	struct pending* pend;
	/* process waiting queries */
	while(outnet->udp_wait_first && outnet->unused_fds 
		&& !outnet->want_to_quit) {
		pend = outnet->udp_wait_first;
		outnet->udp_wait_first = pend->next_waiting;
		if(!pend->next_waiting) outnet->udp_wait_last = NULL;
		sldns_buffer_clear(outnet->udp_buff);
		sldns_buffer_write(outnet->udp_buff, pend->pkt, pend->pkt_len);
		sldns_buffer_flip(outnet->udp_buff);
		free(pend->pkt); /* freeing now makes get_mem correct */
		pend->pkt = NULL; 
		pend->pkt_len = 0;
		if(!randomize_and_send_udp(pend, outnet->udp_buff,
			pend->timeout)) {
			/* callback error on pending */
			if(pend->cb) {
				fptr_ok(fptr_whitelist_pending_udp(pend->cb));
				(void)(*pend->cb)(outnet->unused_fds->cp, pend->cb_arg, 
					NETEVENT_CLOSED, NULL);
			}
			pending_delete(outnet, pend);
		}
	}
}