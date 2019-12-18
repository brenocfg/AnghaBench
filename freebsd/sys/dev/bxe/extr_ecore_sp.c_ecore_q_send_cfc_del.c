#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_3__ {size_t cid_index; } ;
struct TYPE_4__ {TYPE_1__ cfc_del; } ;
struct ecore_queue_state_params {TYPE_2__ params; struct ecore_queue_sp_obj* q_obj; } ;
struct ecore_queue_sp_obj {size_t max_cos; int /*<<< orphan*/ * cids; int /*<<< orphan*/  cl_id; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_ERR (char*,int /*<<< orphan*/ ,size_t) ; 
 int ECORE_INVAL ; 
 int /*<<< orphan*/  NONE_CONNECTION_TYPE ; 
 int /*<<< orphan*/  RAMROD_CMD_ID_COMMON_CFC_DEL ; 
 int ecore_sp_post (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ecore_q_send_cfc_del(struct bxe_softc *sc,
				       struct ecore_queue_state_params *params)
{
	struct ecore_queue_sp_obj *o = params->q_obj;
	uint8_t cid_idx = params->params.cfc_del.cid_index;

	if (cid_idx >= o->max_cos) {
		ECORE_ERR("queue[%d]: cid_index (%d) is out of range\n",
			  o->cl_id, cid_idx);
		return ECORE_INVAL;
	}

	return ecore_sp_post(sc, RAMROD_CMD_ID_COMMON_CFC_DEL,
			     o->cids[cid_idx], 0,
			     NONE_CONNECTION_TYPE);
}