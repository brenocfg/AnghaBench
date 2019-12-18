#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_2__* cfg; } ;
typedef  TYPE_5__ smp_engine_t ;
typedef  int /*<<< orphan*/  smp_comp_cb_t ;
struct TYPE_14__ {unsigned int id; unsigned int mod; } ;
struct TYPE_17__ {int /*<<< orphan*/  mgtclass; int /*<<< orphan*/  mkey; int /*<<< orphan*/  trid; int /*<<< orphan*/  dataoffs; int /*<<< orphan*/  datasz; int /*<<< orphan*/  timeout; TYPE_1__ attr; int /*<<< orphan*/  method; } ;
struct TYPE_16__ {int drslid; int drdlid; } ;
struct TYPE_20__ {scalar_t__ lid; scalar_t__ qp; scalar_t__ sl; TYPE_3__ drpath; } ;
struct TYPE_19__ {TYPE_4__ rpc; TYPE_7__ path; void* cb_data; int /*<<< orphan*/  cb; } ;
typedef  TYPE_6__ ibnd_smp_t ;
typedef  TYPE_7__ ib_portid_t ;
struct TYPE_15__ {int /*<<< orphan*/  mkey; int /*<<< orphan*/  timeout_ms; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IBND_ERROR (char*) ; 
 int /*<<< orphan*/  IB_MAD_METHOD_GET ; 
 int /*<<< orphan*/  IB_SMI_CLASS ; 
 int /*<<< orphan*/  IB_SMI_DIRECT_CLASS ; 
 int /*<<< orphan*/  IB_SMP_DATA_OFFS ; 
 int /*<<< orphan*/  IB_SMP_DATA_SIZE ; 
 TYPE_6__* calloc (int,int) ; 
 int /*<<< orphan*/  mad_trid () ; 
 int process_smp_queue (TYPE_5__*) ; 
 int /*<<< orphan*/  queue_smp (TYPE_5__*,TYPE_6__*) ; 

int issue_smp(smp_engine_t * engine, ib_portid_t * portid,
	      unsigned attrid, unsigned mod, smp_comp_cb_t cb, void *cb_data)
{
	ibnd_smp_t *smp = calloc(1, sizeof *smp);
	if (!smp) {
		IBND_ERROR("OOM\n");
		return -ENOMEM;
	}

	smp->cb = cb;
	smp->cb_data = cb_data;
	smp->path = *portid;
	smp->rpc.method = IB_MAD_METHOD_GET;
	smp->rpc.attr.id = attrid;
	smp->rpc.attr.mod = mod;
	smp->rpc.timeout = engine->cfg->timeout_ms;
	smp->rpc.datasz = IB_SMP_DATA_SIZE;
	smp->rpc.dataoffs = IB_SMP_DATA_OFFS;
	smp->rpc.trid = mad_trid();
	smp->rpc.mkey = engine->cfg->mkey;

	if (portid->lid <= 0 || portid->drpath.drslid == 0xffff ||
	    portid->drpath.drdlid == 0xffff)
		smp->rpc.mgtclass = IB_SMI_DIRECT_CLASS;	/* direct SMI */
	else
		smp->rpc.mgtclass = IB_SMI_CLASS;	/* Lid routed SMI */

	portid->sl = 0;
	portid->qp = 0;

	queue_smp(engine, smp);
	return process_smp_queue(engine);
}