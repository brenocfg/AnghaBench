#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_13__ {int /*<<< orphan*/  total_smps; int /*<<< orphan*/  smps_on_wire; TYPE_2__* cfg; } ;
typedef  TYPE_3__ smp_engine_t ;
struct TYPE_11__ {scalar_t__ trid; } ;
struct TYPE_14__ {TYPE_1__ rpc; } ;
typedef  TYPE_4__ ibnd_smp_t ;
typedef  int /*<<< orphan*/  cl_map_item_t ;
struct TYPE_12__ {scalar_t__ max_smps; } ;

/* Variables and functions */
 scalar_t__ cl_qmap_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_qmap_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 TYPE_4__* get_smp (TYPE_3__*) ; 
 int send_smp (TYPE_4__*,TYPE_3__*) ; 

__attribute__((used)) static int process_smp_queue(smp_engine_t * engine)
{
	int rc = 0;
	ibnd_smp_t *smp;
	while (cl_qmap_count(&engine->smps_on_wire)
	       < engine->cfg->max_smps) {
		smp = get_smp(engine);
		if (!smp)
			return 0;

		if ((rc = send_smp(smp, engine)) != 0) {
			free(smp);
			return rc;
		}
		cl_qmap_insert(&engine->smps_on_wire, (uint32_t) smp->rpc.trid,
			       (cl_map_item_t *) smp);
		engine->total_smps++;
	}
	return 0;
}