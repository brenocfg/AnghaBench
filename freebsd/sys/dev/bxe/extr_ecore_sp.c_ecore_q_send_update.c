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
typedef  size_t uint8_t ;
struct ecore_queue_update_params {size_t cid_index; } ;
struct TYPE_2__ {struct ecore_queue_update_params update; } ;
struct ecore_queue_state_params {TYPE_1__ params; struct ecore_queue_sp_obj* q_obj; } ;
struct ecore_queue_sp_obj {size_t max_cos; int /*<<< orphan*/ * cids; int /*<<< orphan*/  cl_id; int /*<<< orphan*/  rdata_mapping; scalar_t__ rdata; } ;
struct client_update_ramrod_data {int dummy; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  ecore_dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_ERR (char*,int /*<<< orphan*/ ,size_t) ; 
 int ECORE_INVAL ; 
 int /*<<< orphan*/  ECORE_MEMSET (struct client_update_ramrod_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ETH_CONNECTION_TYPE ; 
 int /*<<< orphan*/  RAMROD_CMD_ID_ETH_CLIENT_UPDATE ; 
 int /*<<< orphan*/  ecore_q_fill_update_data (struct bxe_softc*,struct ecore_queue_sp_obj*,struct ecore_queue_update_params*,struct client_update_ramrod_data*) ; 
 int ecore_sp_post (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ecore_q_send_update(struct bxe_softc *sc,
				      struct ecore_queue_state_params *params)
{
	struct ecore_queue_sp_obj *o = params->q_obj;
	struct client_update_ramrod_data *rdata =
		(struct client_update_ramrod_data *)o->rdata;
	ecore_dma_addr_t data_mapping = o->rdata_mapping;
	struct ecore_queue_update_params *update_params =
		&params->params.update;
	uint8_t cid_index = update_params->cid_index;

	if (cid_index >= o->max_cos) {
		ECORE_ERR("queue[%d]: cid_index (%d) is out of range\n",
			  o->cl_id, cid_index);
		return ECORE_INVAL;
	}

	/* Clear the ramrod data */
	ECORE_MEMSET(rdata, 0, sizeof(*rdata));

	/* Fill the ramrod data */
	ecore_q_fill_update_data(sc, o, update_params, rdata);

	/* No need for an explicit memory barrier here as long as we
	 * ensure the ordering of writing to the SPQ element
	 * and updating of the SPQ producer which involves a memory
	 * read. If the memory read is removed we will have to put a
	 * full memory barrier there (inside ecore_sp_post()).
	 */
	return ecore_sp_post(sc, RAMROD_CMD_ID_ETH_CLIENT_UPDATE,
			     o->cids[cid_index], data_mapping,
			     ETH_CONNECTION_TYPE);
}