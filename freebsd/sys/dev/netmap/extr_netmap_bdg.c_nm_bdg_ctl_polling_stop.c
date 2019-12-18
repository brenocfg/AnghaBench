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
struct nm_bdg_polling_state {int configured; } ;
struct netmap_bwrap_adapter {int /*<<< orphan*/  hwna; struct nm_bdg_polling_state* na_polling_state; } ;
struct netmap_adapter {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  nm_bdg_polling_stop_delete_kthreads (struct nm_bdg_polling_state*) ; 
 int /*<<< orphan*/  nm_os_free (struct nm_bdg_polling_state*) ; 
 int /*<<< orphan*/  nm_prerr (char*) ; 
 int /*<<< orphan*/  nma_intr_enable (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nm_bdg_ctl_polling_stop(struct netmap_adapter *na)
{
	struct netmap_bwrap_adapter *bna = (struct netmap_bwrap_adapter *)na;
	struct nm_bdg_polling_state *bps;

	if (!bna->na_polling_state) {
		nm_prerr("ERROR adapter is not in polling mode");
		return EFAULT;
	}
	bps = bna->na_polling_state;
	nm_bdg_polling_stop_delete_kthreads(bna->na_polling_state);
	bps->configured = false;
	nm_os_free(bps);
	bna->na_polling_state = NULL;
	/* reenable interrupts */
	nma_intr_enable(bna->hwna, 1);
	return 0;
}