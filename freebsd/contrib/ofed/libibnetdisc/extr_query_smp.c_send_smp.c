#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {int smi_agent; int smi_dir_agent; TYPE_1__* cfg; int /*<<< orphan*/  umad_fd; } ;
typedef  TYPE_2__ smp_engine_t ;
struct TYPE_11__ {scalar_t__ mgtclass; } ;
struct TYPE_10__ {int /*<<< orphan*/  path; TYPE_4__ rpc; } ;
typedef  TYPE_3__ ibnd_smp_t ;
typedef  TYPE_4__ ib_rpc_t ;
struct TYPE_8__ {int /*<<< orphan*/  retries; int /*<<< orphan*/  timeout_ms; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IBND_ERROR (char*,...) ; 
 scalar_t__ IB_MAD_SIZE ; 
 scalar_t__ IB_SMI_CLASS ; 
 scalar_t__ IB_SMI_DIRECT_CLASS ; 
 int mad_build_pkt (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int umad_send (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ umad_size () ; 

__attribute__((used)) static int send_smp(ibnd_smp_t * smp, smp_engine_t * engine)
{
	int rc = 0;
	uint8_t umad[1024];
	ib_rpc_t *rpc = &smp->rpc;
	int agent = 0;

	memset(umad, 0, umad_size() + IB_MAD_SIZE);

	if (rpc->mgtclass == IB_SMI_CLASS) {
		agent = engine->smi_agent;
	} else if (rpc->mgtclass == IB_SMI_DIRECT_CLASS) {
		agent = engine->smi_dir_agent;
	} else {
		IBND_ERROR("Invalid class for RPC\n");
		return (-EIO);
	}

	if ((rc = mad_build_pkt(umad, &smp->rpc, &smp->path, NULL, NULL))
	    < 0) {
		IBND_ERROR("mad_build_pkt failed; %d\n", rc);
		return rc;
	}

	if ((rc = umad_send(engine->umad_fd, agent, umad, IB_MAD_SIZE,
			    engine->cfg->timeout_ms, engine->cfg->retries)) < 0) {
		IBND_ERROR("send failed; %d\n", rc);
		return rc;
	}

	return 0;
}