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
struct ecore_queue_sp_obj {int /*<<< orphan*/ * cids; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 size_t ECORE_PRIMARY_CID_INDEX ; 
 int /*<<< orphan*/  ETH_CONNECTION_TYPE ; 
 int /*<<< orphan*/  RAMROD_CMD_ID_ETH_EMPTY ; 
 int ecore_sp_post (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ecore_q_send_empty(struct bxe_softc *sc,
				     struct ecore_queue_state_params *params)
{
	struct ecore_queue_sp_obj *o = params->q_obj;

	return ecore_sp_post(sc, RAMROD_CMD_ID_ETH_EMPTY,
			     o->cids[ECORE_PRIMARY_CID_INDEX], 0,
			     ETH_CONNECTION_TYPE);
}