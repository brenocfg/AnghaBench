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
struct nmreq_vale_polling {int dummy; } ;
struct nm_bdg_polling_state {int configured; int stopped; struct nm_bdg_polling_state* kthreads; struct netmap_bwrap_adapter* bna; } ;
struct netmap_bwrap_adapter {int /*<<< orphan*/  hwna; struct nm_bdg_polling_state* na_polling_state; } ;
struct netmap_adapter {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ get_polling_cfg (struct nmreq_vale_polling*,struct netmap_adapter*,struct nm_bdg_polling_state*) ; 
 scalar_t__ nm_bdg_create_kthreads (struct nm_bdg_polling_state*) ; 
 int nm_bdg_polling_start_kthreads (struct nm_bdg_polling_state*) ; 
 int /*<<< orphan*/  nm_os_free (struct nm_bdg_polling_state*) ; 
 struct nm_bdg_polling_state* nm_os_malloc (int) ; 
 int /*<<< orphan*/  nm_prerr (char*) ; 
 int /*<<< orphan*/  nma_intr_enable (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nm_bdg_ctl_polling_start(struct nmreq_vale_polling *req, struct netmap_adapter *na)
{
	struct nm_bdg_polling_state *bps;
	struct netmap_bwrap_adapter *bna;
	int error;

	bna = (struct netmap_bwrap_adapter *)na;
	if (bna->na_polling_state) {
		nm_prerr("ERROR adapter already in polling mode");
		return EFAULT;
	}

	bps = nm_os_malloc(sizeof(*bps));
	if (!bps)
		return ENOMEM;
	bps->configured = false;
	bps->stopped = true;

	if (get_polling_cfg(req, na, bps)) {
		nm_os_free(bps);
		return EINVAL;
	}

	if (nm_bdg_create_kthreads(bps)) {
		nm_os_free(bps);
		return EFAULT;
	}

	bps->configured = true;
	bna->na_polling_state = bps;
	bps->bna = bna;

	/* disable interrupts if possible */
	nma_intr_enable(bna->hwna, 0);
	/* start kthread now */
	error = nm_bdg_polling_start_kthreads(bps);
	if (error) {
		nm_prerr("ERROR nm_bdg_polling_start_kthread()");
		nm_os_free(bps->kthreads);
		nm_os_free(bps);
		bna->na_polling_state = NULL;
		nma_intr_enable(bna->hwna, 1);
	}
	return error;
}