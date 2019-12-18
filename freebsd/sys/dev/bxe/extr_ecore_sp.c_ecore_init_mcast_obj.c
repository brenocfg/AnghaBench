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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  macs; } ;
struct TYPE_4__ {TYPE_1__ exact_match; } ;
struct ecore_mcast_obj {int max_cmd_len; void* set_registry_size; void* get_registry_size; int /*<<< orphan*/  revert; int /*<<< orphan*/  validate; int /*<<< orphan*/ * set_one_rule; void* wait_comp; void* check_pending; int /*<<< orphan*/ * hdl_restore; int /*<<< orphan*/ * enqueue_cmd; int /*<<< orphan*/  config_mcast; TYPE_2__ registry; int /*<<< orphan*/  clear_sched; int /*<<< orphan*/  set_sched; int /*<<< orphan*/  check_sched; int /*<<< orphan*/  sched_state; int /*<<< orphan*/  pending_cmds_head; int /*<<< orphan*/  engine_id; int /*<<< orphan*/  raw; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  ecore_obj_type ;
typedef  int /*<<< orphan*/  ecore_dma_addr_t ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E1 (struct bxe_softc*) ; 
 scalar_t__ CHIP_IS_E1H (struct bxe_softc*) ; 
 scalar_t__ CHIP_REV_IS_SLOW (struct bxe_softc*) ; 
 int /*<<< orphan*/  ECORE_FILTER_MCAST_SCHED ; 
 int /*<<< orphan*/  ECORE_LIST_INIT (int /*<<< orphan*/ *) ; 
 int ECORE_MAX_EMUL_MULTI ; 
 int ECORE_MAX_MULTICAST ; 
 int /*<<< orphan*/  ECORE_MEMSET (struct ecore_mcast_obj*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ecore_init_raw_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int,unsigned long*,int /*<<< orphan*/ ) ; 
 void* ecore_mcast_check_pending ; 
 int /*<<< orphan*/  ecore_mcast_check_sched ; 
 int /*<<< orphan*/  ecore_mcast_clear_sched ; 
 void* ecore_mcast_enqueue_cmd ; 
 void* ecore_mcast_get_registry_size_aprox ; 
 void* ecore_mcast_get_registry_size_exact ; 
 int /*<<< orphan*/ * ecore_mcast_handle_restore_cmd_e1 ; 
 int /*<<< orphan*/ * ecore_mcast_handle_restore_cmd_e2 ; 
 int /*<<< orphan*/  ecore_mcast_revert_e1 ; 
 int /*<<< orphan*/  ecore_mcast_revert_e1h ; 
 int /*<<< orphan*/  ecore_mcast_revert_e2 ; 
 int /*<<< orphan*/ * ecore_mcast_set_one_rule_e1 ; 
 int /*<<< orphan*/ * ecore_mcast_set_one_rule_e2 ; 
 void* ecore_mcast_set_registry_size_aprox ; 
 void* ecore_mcast_set_registry_size_exact ; 
 int /*<<< orphan*/  ecore_mcast_set_sched ; 
 int /*<<< orphan*/  ecore_mcast_setup_e1 ; 
 int /*<<< orphan*/  ecore_mcast_setup_e1h ; 
 int /*<<< orphan*/  ecore_mcast_setup_e2 ; 
 int /*<<< orphan*/  ecore_mcast_validate_e1 ; 
 int /*<<< orphan*/  ecore_mcast_validate_e1h ; 
 int /*<<< orphan*/  ecore_mcast_validate_e2 ; 
 void* ecore_mcast_wait ; 

void ecore_init_mcast_obj(struct bxe_softc *sc,
			  struct ecore_mcast_obj *mcast_obj,
			  uint8_t mcast_cl_id, uint32_t mcast_cid, uint8_t func_id,
			  uint8_t engine_id, void *rdata, ecore_dma_addr_t rdata_mapping,
			  int state, unsigned long *pstate, ecore_obj_type type)
{
	ECORE_MEMSET(mcast_obj, 0, sizeof(*mcast_obj));

	ecore_init_raw_obj(&mcast_obj->raw, mcast_cl_id, mcast_cid, func_id,
			   rdata, rdata_mapping, state, pstate, type);

	mcast_obj->engine_id = engine_id;

	ECORE_LIST_INIT(&mcast_obj->pending_cmds_head);

	mcast_obj->sched_state = ECORE_FILTER_MCAST_SCHED;
	mcast_obj->check_sched = ecore_mcast_check_sched;
	mcast_obj->set_sched = ecore_mcast_set_sched;
	mcast_obj->clear_sched = ecore_mcast_clear_sched;

	if (CHIP_IS_E1(sc)) {
		mcast_obj->config_mcast      = ecore_mcast_setup_e1;
		mcast_obj->enqueue_cmd       = ecore_mcast_enqueue_cmd;
		mcast_obj->hdl_restore       =
			ecore_mcast_handle_restore_cmd_e1;
		mcast_obj->check_pending     = ecore_mcast_check_pending;

		if (CHIP_REV_IS_SLOW(sc))
			mcast_obj->max_cmd_len = ECORE_MAX_EMUL_MULTI;
		else
			mcast_obj->max_cmd_len = ECORE_MAX_MULTICAST;

		mcast_obj->wait_comp         = ecore_mcast_wait;
		mcast_obj->set_one_rule      = ecore_mcast_set_one_rule_e1;
		mcast_obj->validate          = ecore_mcast_validate_e1;
		mcast_obj->revert            = ecore_mcast_revert_e1;
		mcast_obj->get_registry_size =
			ecore_mcast_get_registry_size_exact;
		mcast_obj->set_registry_size =
			ecore_mcast_set_registry_size_exact;

		/* 57710 is the only chip that uses the exact match for mcast
		 * at the moment.
		 */
		ECORE_LIST_INIT(&mcast_obj->registry.exact_match.macs);

	} else if (CHIP_IS_E1H(sc)) {
		mcast_obj->config_mcast  = ecore_mcast_setup_e1h;
		mcast_obj->enqueue_cmd   = NULL;
		mcast_obj->hdl_restore   = NULL;
		mcast_obj->check_pending = ecore_mcast_check_pending;

		/* 57711 doesn't send a ramrod, so it has unlimited credit
		 * for one command.
		 */
		mcast_obj->max_cmd_len       = -1;
		mcast_obj->wait_comp         = ecore_mcast_wait;
		mcast_obj->set_one_rule      = NULL;
		mcast_obj->validate          = ecore_mcast_validate_e1h;
		mcast_obj->revert            = ecore_mcast_revert_e1h;
		mcast_obj->get_registry_size =
			ecore_mcast_get_registry_size_aprox;
		mcast_obj->set_registry_size =
			ecore_mcast_set_registry_size_aprox;
	} else {
		mcast_obj->config_mcast      = ecore_mcast_setup_e2;
		mcast_obj->enqueue_cmd       = ecore_mcast_enqueue_cmd;
		mcast_obj->hdl_restore       =
			ecore_mcast_handle_restore_cmd_e2;
		mcast_obj->check_pending     = ecore_mcast_check_pending;
		/* TODO: There should be a proper HSI define for this number!!!
		 */
		mcast_obj->max_cmd_len       = 16;
		mcast_obj->wait_comp         = ecore_mcast_wait;
		mcast_obj->set_one_rule      = ecore_mcast_set_one_rule_e2;
		mcast_obj->validate          = ecore_mcast_validate_e2;
		mcast_obj->revert            = ecore_mcast_revert_e2;
		mcast_obj->get_registry_size =
			ecore_mcast_get_registry_size_aprox;
		mcast_obj->set_registry_size =
			ecore_mcast_set_registry_size_aprox;
	}
}