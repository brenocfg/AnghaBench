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
typedef  scalar_t__ u_int ;
struct netmap_kring {scalar_t__ nkr_num_slots; scalar_t__ rhead; scalar_t__ nr_hwcur; scalar_t__ nr_hwtail; struct netmap_adapter* na; } ;
struct netmap_adapter {int /*<<< orphan*/  ifp; } ;
struct mbq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mbq_init (struct mbq*) ; 
 int /*<<< orphan*/  mbq_len (struct mbq*) ; 
 int /*<<< orphan*/  netmap_grab_packets (struct netmap_kring*,struct mbq*,int) ; 
 int /*<<< orphan*/  netmap_send_up (int /*<<< orphan*/ ,struct mbq*) ; 
 int /*<<< orphan*/  nm_prdis (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
netmap_txsync_to_host(struct netmap_kring *kring, int flags)
{
	struct netmap_adapter *na = kring->na;
	u_int const lim = kring->nkr_num_slots - 1;
	u_int const head = kring->rhead;
	struct mbq q;

	/* Take packets from hwcur to head and pass them up.
	 * Force hwcur = head since netmap_grab_packets() stops at head
	 */
	mbq_init(&q);
	netmap_grab_packets(kring, &q, 1 /* force */);
	nm_prdis("have %d pkts in queue", mbq_len(&q));
	kring->nr_hwcur = head;
	kring->nr_hwtail = head + lim;
	if (kring->nr_hwtail > lim)
		kring->nr_hwtail -= lim + 1;

	netmap_send_up(na->ifp, &q);
	return 0;
}