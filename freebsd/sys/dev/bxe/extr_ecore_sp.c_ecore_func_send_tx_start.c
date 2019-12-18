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
struct flow_control_configuration {int /*<<< orphan*/ * dcb_outer_pri; int /*<<< orphan*/ * traffic_type_to_priority_cos; int /*<<< orphan*/  dont_add_pri_0; int /*<<< orphan*/  dcb_version; int /*<<< orphan*/  dcb_enabled; } ;
struct ecore_func_tx_start_params {int /*<<< orphan*/ * dcb_outer_pri; int /*<<< orphan*/ * traffic_type_to_priority_cos; int /*<<< orphan*/  dont_add_pri_0; int /*<<< orphan*/  dcb_version; int /*<<< orphan*/  dcb_enabled; } ;
struct TYPE_2__ {struct ecore_func_tx_start_params tx_start; } ;
struct ecore_func_state_params {TYPE_1__ params; struct ecore_func_sp_obj* f_obj; } ;
struct ecore_func_sp_obj {int /*<<< orphan*/  rdata_mapping; scalar_t__ rdata; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  ecore_dma_addr_t ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ECORE_MEMSET (struct flow_control_configuration*,int /*<<< orphan*/ ,int) ; 
 int MAX_TRAFFIC_TYPES ; 
 int /*<<< orphan*/  NONE_CONNECTION_TYPE ; 
 int /*<<< orphan*/  RAMROD_CMD_ID_COMMON_START_TRAFFIC ; 
 int ecore_sp_post (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ecore_func_send_tx_start(struct bxe_softc *sc,
				       struct ecore_func_state_params *params)
{
	struct ecore_func_sp_obj *o = params->f_obj;
	struct flow_control_configuration *rdata =
		(struct flow_control_configuration *)o->rdata;
	ecore_dma_addr_t data_mapping = o->rdata_mapping;
	struct ecore_func_tx_start_params *tx_start_params =
		&params->params.tx_start;
	int i;

	ECORE_MEMSET(rdata, 0, sizeof(*rdata));

	rdata->dcb_enabled = tx_start_params->dcb_enabled;
	rdata->dcb_version = tx_start_params->dcb_version;
	rdata->dont_add_pri_0 = tx_start_params->dont_add_pri_0;

	for (i = 0; i < ARRAY_SIZE(rdata->traffic_type_to_priority_cos); i++)
		rdata->traffic_type_to_priority_cos[i] =
			tx_start_params->traffic_type_to_priority_cos[i];

	for (i = 0; i < MAX_TRAFFIC_TYPES; i++)
		rdata->dcb_outer_pri[i] = tx_start_params->dcb_outer_pri[i];

	/* No need for an explicit memory barrier here as long as we
	 * ensure the ordering of writing to the SPQ element
	 * and updating of the SPQ producer which involves a memory
	 * read. If the memory read is removed we will have to put a
	 * full memory barrier there (inside ecore_sp_post()).
	 */
	return ecore_sp_post(sc, RAMROD_CMD_ID_COMMON_START_TRAFFIC, 0,
			     data_mapping, NONE_CONNECTION_TYPE);
}