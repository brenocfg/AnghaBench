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
struct ecore_queue_sp_obj {int /*<<< orphan*/ * cids; scalar_t__ cl_id; } ;
struct bxe_softc {int dummy; } ;
typedef  scalar_t__ ecore_dma_addr_t ;

/* Variables and functions */
 size_t ECORE_PRIMARY_CID_INDEX ; 
 int /*<<< orphan*/  ETH_CONNECTION_TYPE ; 
 int /*<<< orphan*/  RAMROD_CMD_ID_ETH_HALT ; 
 int ecore_sp_post (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ecore_q_send_halt(struct bxe_softc *sc,
				    struct ecore_queue_state_params *params)
{
	struct ecore_queue_sp_obj *o = params->q_obj;

	/* build eth_halt_ramrod_data.client_id in a big-endian friendly way */
	ecore_dma_addr_t data_mapping = 0;
	data_mapping = (ecore_dma_addr_t)o->cl_id;

	/* No need for an explicit memory barrier here as long as we
	 * ensure the ordering of writing to the SPQ element
	 * and updating of the SPQ producer which involves a memory
	 * read. If the memory read is removed we will have to put a
	 * full memory barrier there (inside ecore_sp_post()).
	 */
	return ecore_sp_post(sc,
			     RAMROD_CMD_ID_ETH_HALT,
			     o->cids[ECORE_PRIMARY_CID_INDEX],
			     data_mapping,
			     ETH_CONNECTION_TYPE);
}