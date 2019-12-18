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
struct nm_bdg_polling_state {int ncpus; int stopped; struct nm_bdg_kthread* kthreads; } ;
struct nm_bdg_kthread {int /*<<< orphan*/  nmk; } ;

/* Variables and functions */
 int /*<<< orphan*/  nm_os_kctx_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nm_os_kctx_worker_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nm_bdg_polling_stop_delete_kthreads(struct nm_bdg_polling_state *bps)
{
	int i;

	if (!bps)
		return;

	for (i = 0; i < bps->ncpus; i++) {
		struct nm_bdg_kthread *t = bps->kthreads + i;
		nm_os_kctx_worker_stop(t->nmk);
		nm_os_kctx_destroy(t->nmk);
	}
	bps->stopped = true;
}