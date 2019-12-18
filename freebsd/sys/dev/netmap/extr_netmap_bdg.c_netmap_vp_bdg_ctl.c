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
struct nmreq_header {scalar_t__ nr_reqtype; } ;
struct nm_bridge {int dummy; } ;
struct netmap_vp_adapter {struct nm_bridge* na_bdg; int /*<<< orphan*/  bdg_port; } ;
struct netmap_adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ NETMAP_REQ_VALE_ATTACH ; 
 int /*<<< orphan*/  netmap_adapter_put (struct netmap_adapter*) ; 
 int /*<<< orphan*/  netmap_bdg_detach_common (struct nm_bridge*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netmap_set_all_rings (struct netmap_adapter*,int) ; 

int
netmap_vp_bdg_ctl(struct nmreq_header *hdr, struct netmap_adapter *na)
{
	struct netmap_vp_adapter *vpna = (struct netmap_vp_adapter *)na;
	struct nm_bridge *b = vpna->na_bdg;

	if (hdr->nr_reqtype == NETMAP_REQ_VALE_ATTACH) {
		return 0; /* nothing to do */
	}
	if (b) {
		netmap_set_all_rings(na, 0 /* disable */);
		netmap_bdg_detach_common(b, vpna->bdg_port, -1);
		vpna->na_bdg = NULL;
		netmap_set_all_rings(na, 1 /* enable */);
	}
	/* I have took reference just for attach */
	netmap_adapter_put(na);
	return 0;
}