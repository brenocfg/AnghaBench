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
struct nm_kctx_cfg {int type; struct nm_bdg_kthread* worker_private; int /*<<< orphan*/  worker_fn; } ;
struct nm_bdg_polling_state {int ncpus; scalar_t__ mode; int cpu_from; int qfirst; int qlast; struct nm_bdg_kthread* kthreads; } ;
struct nm_bdg_kthread {int qfirst; int qlast; int /*<<< orphan*/ * nmk; struct nm_bdg_polling_state* bps; } ;
typedef  int /*<<< orphan*/  kcfg ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 scalar_t__ NETMAP_POLLING_MODE_SINGLE_CPU ; 
 int /*<<< orphan*/  bzero (struct nm_kctx_cfg*,int) ; 
 int /*<<< orphan*/  netmap_bwrap_polling ; 
 scalar_t__ netmap_verbose ; 
 int /*<<< orphan*/  nm_os_free (struct nm_bdg_kthread*) ; 
 int /*<<< orphan*/ * nm_os_kctx_create (struct nm_kctx_cfg*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nm_os_kctx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nm_os_kctx_worker_setaff (int /*<<< orphan*/ *,int) ; 
 struct nm_bdg_kthread* nm_os_malloc (int) ; 
 int /*<<< orphan*/  nm_prinf (char*,int,int,int,int) ; 

__attribute__((used)) static int
nm_bdg_create_kthreads(struct nm_bdg_polling_state *bps)
{
	struct nm_kctx_cfg kcfg;
	int i, j;

	bps->kthreads = nm_os_malloc(sizeof(struct nm_bdg_kthread) * bps->ncpus);
	if (bps->kthreads == NULL)
		return ENOMEM;

	bzero(&kcfg, sizeof(kcfg));
	kcfg.worker_fn = netmap_bwrap_polling;
	for (i = 0; i < bps->ncpus; i++) {
		struct nm_bdg_kthread *t = bps->kthreads + i;
		int all = (bps->ncpus == 1 &&
			bps->mode == NETMAP_POLLING_MODE_SINGLE_CPU);
		int affinity = bps->cpu_from + i;

		t->bps = bps;
		t->qfirst = all ? bps->qfirst /* must be 0 */: affinity;
		t->qlast = all ? bps->qlast : t->qfirst + 1;
		if (netmap_verbose)
			nm_prinf("kthread %d a:%u qf:%u ql:%u", i, affinity, t->qfirst,
				t->qlast);

		kcfg.type = i;
		kcfg.worker_private = t;
		t->nmk = nm_os_kctx_create(&kcfg, NULL);
		if (t->nmk == NULL) {
			goto cleanup;
		}
		nm_os_kctx_worker_setaff(t->nmk, affinity);
	}
	return 0;

cleanup:
	for (j = 0; j < i; j++) {
		struct nm_bdg_kthread *t = bps->kthreads + i;
		nm_os_kctx_destroy(t->nmk);
	}
	nm_os_free(bps->kthreads);
	return EFAULT;
}