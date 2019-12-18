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
struct netmap_adapter {size_t num_rx_rings; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_queue; } ;

/* Variables and functions */
 TYPE_1__** NMR (struct netmap_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NR_RX ; 
 int /*<<< orphan*/  mbq_safe_init (int /*<<< orphan*/ *) ; 
 int netmap_krings_create (struct netmap_adapter*,int /*<<< orphan*/ ) ; 
 size_t netmap_real_rings (struct netmap_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nm_prdis (char*,size_t) ; 

int
netmap_hw_krings_create(struct netmap_adapter *na)
{
	int ret = netmap_krings_create(na, 0);
	if (ret == 0) {
		/* initialize the mbq for the sw rx ring */
		u_int lim = netmap_real_rings(na, NR_RX), i;
		for (i = na->num_rx_rings; i < lim; i++) {
			mbq_safe_init(&NMR(na, NR_RX)[i]->rx_queue);
		}
		nm_prdis("initialized sw rx queue %d", na->num_rx_rings);
	}
	return ret;
}