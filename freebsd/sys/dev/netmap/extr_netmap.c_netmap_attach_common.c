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
struct netmap_adapter {int na_flags; int num_host_rx_rings; int num_host_tx_rings; int /*<<< orphan*/ * nm_bdg_attach; int /*<<< orphan*/ * nm_mem; scalar_t__ active_fds; int /*<<< orphan*/ * nm_notify; int /*<<< orphan*/  nm_krings_delete; int /*<<< orphan*/ * nm_krings_create; struct netmap_adapter* pdev; TYPE_1__* ifp; int /*<<< orphan*/  if_input; scalar_t__ rx_buf_maxsize; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_input; } ;

/* Variables and functions */
 int NAF_HOST_RINGS ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/ * netmap_default_bdg_attach ; 
 int /*<<< orphan*/ * netmap_hw_krings_create ; 
 int /*<<< orphan*/  netmap_hw_krings_delete ; 
 int /*<<< orphan*/ * netmap_mem_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * netmap_notify ; 
 int /*<<< orphan*/  nm_mem ; 

int
netmap_attach_common(struct netmap_adapter *na)
{
	if (!na->rx_buf_maxsize) {
		/* Set a conservative default (larger is safer). */
		na->rx_buf_maxsize = PAGE_SIZE;
	}

#ifdef __FreeBSD__
	if (na->na_flags & NAF_HOST_RINGS && na->ifp) {
		na->if_input = na->ifp->if_input; /* for netmap_send_up */
	}
	na->pdev = na; /* make sure netmap_mem_map() is called */
#endif /* __FreeBSD__ */
	if (na->na_flags & NAF_HOST_RINGS) {
		if (na->num_host_rx_rings == 0)
			na->num_host_rx_rings = 1;
		if (na->num_host_tx_rings == 0)
			na->num_host_tx_rings = 1;
	}
	if (na->nm_krings_create == NULL) {
		/* we assume that we have been called by a driver,
		 * since other port types all provide their own
		 * nm_krings_create
		 */
		na->nm_krings_create = netmap_hw_krings_create;
		na->nm_krings_delete = netmap_hw_krings_delete;
	}
	if (na->nm_notify == NULL)
		na->nm_notify = netmap_notify;
	na->active_fds = 0;

	if (na->nm_mem == NULL) {
		/* use the global allocator */
		na->nm_mem = netmap_mem_get(&nm_mem);
	}
#ifdef WITH_VALE
	if (na->nm_bdg_attach == NULL)
		/* no special nm_bdg_attach callback. On VALE
		 * attach, we need to interpose a bwrap
		 */
		na->nm_bdg_attach = netmap_default_bdg_attach;
#endif

	return 0;
}