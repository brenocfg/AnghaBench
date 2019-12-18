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
typedef  size_t u_int ;
struct netmap_adapter {int dummy; } ;
struct mbq {int dummy; } ;
struct TYPE_2__ {struct mbq rx_queue; } ;

/* Variables and functions */
 TYPE_1__** NMR (struct netmap_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NR_RX ; 
 int /*<<< orphan*/  mbq_len (struct mbq*) ; 
 int /*<<< orphan*/  mbq_purge (struct mbq*) ; 
 int /*<<< orphan*/  mbq_safe_fini (struct mbq*) ; 
 int /*<<< orphan*/  netmap_krings_delete (struct netmap_adapter*) ; 
 size_t netmap_real_rings (struct netmap_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nm_prdis (char*,int /*<<< orphan*/ ) ; 
 size_t nma_get_nrings (struct netmap_adapter*,int /*<<< orphan*/ ) ; 

void
netmap_hw_krings_delete(struct netmap_adapter *na)
{
	u_int lim = netmap_real_rings(na, NR_RX), i;

	for (i = nma_get_nrings(na, NR_RX); i < lim; i++) {
		struct mbq *q = &NMR(na, NR_RX)[i]->rx_queue;
		nm_prdis("destroy sw mbq with len %d", mbq_len(q));
		mbq_purge(q);
		mbq_safe_fini(q);
	}
	netmap_krings_delete(na);
}