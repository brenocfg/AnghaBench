#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct taskqgroup {int dummy; } ;
struct grouptask {int dummy; } ;
typedef  int iflib_intr_type_t ;
typedef  TYPE_3__* if_irq_t ;
typedef  TYPE_4__* if_ctx_t ;
typedef  int /*<<< orphan*/  gtask_fn_t ;
struct TYPE_12__ {int /*<<< orphan*/ * ifc_dev; struct grouptask ifc_vflr_task; TYPE_2__* ifc_rxqs; TYPE_1__* ifc_txqs; } ;
struct TYPE_11__ {int /*<<< orphan*/ * ii_res; } ;
struct TYPE_10__ {struct grouptask ifr_task; } ;
struct TYPE_9__ {struct grouptask ift_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  GROUPTASK_INIT (struct grouptask*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
#define  IFLIB_INTR_IOV 130 
#define  IFLIB_INTR_RX 129 
#define  IFLIB_INTR_TX 128 
 int /*<<< orphan*/ * _task_fn_iov ; 
 int /*<<< orphan*/ * _task_fn_rx ; 
 int /*<<< orphan*/ * _task_fn_tx ; 
 int iflib_irq_set_affinity (TYPE_4__*,TYPE_3__*,int,int,struct grouptask*,struct taskqgroup*,void*,char const*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 struct taskqgroup* qgroup_if_config_tqg ; 
 struct taskqgroup* qgroup_if_io_tqg ; 
 int /*<<< orphan*/  taskqgroup_attach (struct taskqgroup*,struct grouptask*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

void
iflib_softirq_alloc_generic(if_ctx_t ctx, if_irq_t irq, iflib_intr_type_t type, void *arg, int qid, const char *name)
{
	struct grouptask *gtask;
	struct taskqgroup *tqg;
	gtask_fn_t *fn;
	void *q;
	int err;

	switch (type) {
	case IFLIB_INTR_TX:
		q = &ctx->ifc_txqs[qid];
		gtask = &ctx->ifc_txqs[qid].ift_task;
		tqg = qgroup_if_io_tqg;
		fn = _task_fn_tx;
		break;
	case IFLIB_INTR_RX:
		q = &ctx->ifc_rxqs[qid];
		gtask = &ctx->ifc_rxqs[qid].ifr_task;
		tqg = qgroup_if_io_tqg;
		fn = _task_fn_rx;
		break;
	case IFLIB_INTR_IOV:
		q = ctx;
		gtask = &ctx->ifc_vflr_task;
		tqg = qgroup_if_config_tqg;
		fn = _task_fn_iov;
		break;
	default:
		panic("unknown net intr type");
	}
	GROUPTASK_INIT(gtask, 0, fn, q);
	if (irq != NULL) {
		err = iflib_irq_set_affinity(ctx, irq, type, qid, gtask, tqg,
		    q, name);
		if (err)
			taskqgroup_attach(tqg, gtask, q, ctx->ifc_dev,
			    irq->ii_res, name);
	} else {
		taskqgroup_attach(tqg, gtask, q, NULL, NULL, name);
	}
}