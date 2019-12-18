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
struct ecore_queue_state_params {struct ecore_queue_sp_obj* q_obj; } ;
struct ecore_queue_sp_obj {int /*<<< orphan*/ * cids; int /*<<< orphan*/  rdata_mapping; scalar_t__ rdata; } ;
struct client_init_ramrod_data {int dummy; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  ecore_dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_MEMSET (struct client_init_ramrod_data*,int /*<<< orphan*/ ,int) ; 
 size_t ECORE_PRIMARY_CID_INDEX ; 
 int /*<<< orphan*/  ETH_CONNECTION_TYPE ; 
 int RAMROD_CMD_ID_ETH_CLIENT_SETUP ; 
 int /*<<< orphan*/  ecore_q_fill_setup_data_cmn (struct bxe_softc*,struct ecore_queue_state_params*,struct client_init_ramrod_data*) ; 
 int /*<<< orphan*/  ecore_q_fill_setup_data_e2 (struct bxe_softc*,struct ecore_queue_state_params*,struct client_init_ramrod_data*) ; 
 int ecore_sp_post (struct bxe_softc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ecore_q_send_setup_e2(struct bxe_softc *sc,
					struct ecore_queue_state_params *params)
{
	struct ecore_queue_sp_obj *o = params->q_obj;
	struct client_init_ramrod_data *rdata =
		(struct client_init_ramrod_data *)o->rdata;
	ecore_dma_addr_t data_mapping = o->rdata_mapping;
	int ramrod = RAMROD_CMD_ID_ETH_CLIENT_SETUP;

	/* Clear the ramrod data */
	ECORE_MEMSET(rdata, 0, sizeof(*rdata));

	/* Fill the ramrod data */
	ecore_q_fill_setup_data_cmn(sc, params, rdata);
	ecore_q_fill_setup_data_e2(sc, params, rdata);

	/* No need for an explicit memory barrier here as long as we
	 * ensure the ordering of writing to the SPQ element
	 * and updating of the SPQ producer which involves a memory
	 * read. If the memory read is removed we will have to put a
	 * full memory barrier there (inside ecore_sp_post()).
	 */
	return ecore_sp_post(sc,
			     ramrod,
			     o->cids[ECORE_PRIMARY_CID_INDEX],
			     data_mapping,
			     ETH_CONNECTION_TYPE);
}