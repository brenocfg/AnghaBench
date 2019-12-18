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
typedef  int /*<<< orphan*/  uint8_t ;
struct mac_configuration_cmd {TYPE_1__* config_table; } ;
struct ecore_raw_obj {int /*<<< orphan*/  rdata_mapping; int /*<<< orphan*/  cid; int /*<<< orphan*/  (* clear_pending ) (struct ecore_raw_obj*) ;scalar_t__ rdata; } ;
struct ecore_mcast_ramrod_params {int /*<<< orphan*/  ramrod_flags; struct ecore_mcast_obj* mcast_obj; } ;
struct ecore_mcast_obj {int max_cmd_len; int total_pending_num; int /*<<< orphan*/  (* clear_sched ) (struct ecore_mcast_obj*) ;int /*<<< orphan*/  pending_cmds_head; struct ecore_raw_obj raw; } ;
struct bxe_softc {int dummy; } ;
typedef  enum ecore_mcast_cmd { ____Placeholder_ecore_mcast_cmd } ecore_mcast_cmd ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_DBG_BREAK_IF (int) ; 
 scalar_t__ ECORE_LIST_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ECORE_MEMSET (struct mac_configuration_cmd*,int /*<<< orphan*/ ,int) ; 
 int ECORE_PENDING ; 
 int /*<<< orphan*/  ECORE_SET_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ECORE_SUCCESS ; 
 scalar_t__ ECORE_TEST_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ETH_CONNECTION_TYPE ; 
 int /*<<< orphan*/  MAC_CONFIGURATION_ENTRY_ACTION_TYPE ; 
 int /*<<< orphan*/  RAMROD_CMD_ID_ETH_SET_MAC ; 
 int /*<<< orphan*/  RAMROD_DRV_CLR_ONLY ; 
 int /*<<< orphan*/  T_ETH_MAC_COMMAND_INVALIDATE ; 
 int ecore_mcast_handle_current_cmd (struct bxe_softc*,struct ecore_mcast_ramrod_params*,int,int /*<<< orphan*/ ) ; 
 int ecore_mcast_handle_pending_cmds_e1 (struct bxe_softc*,struct ecore_mcast_ramrod_params*) ; 
 int ecore_mcast_refresh_registry_e1 (struct bxe_softc*,struct ecore_mcast_obj*) ; 
 int /*<<< orphan*/  ecore_mcast_set_rdata_hdr_e1 (struct bxe_softc*,struct ecore_mcast_ramrod_params*,int /*<<< orphan*/ ) ; 
 int ecore_sp_post (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ecore_mcast_obj*) ; 
 int /*<<< orphan*/  stub2 (struct ecore_raw_obj*) ; 

__attribute__((used)) static int ecore_mcast_setup_e1(struct bxe_softc *sc,
				struct ecore_mcast_ramrod_params *p,
				enum ecore_mcast_cmd cmd)
{
	struct ecore_mcast_obj *o = p->mcast_obj;
	struct ecore_raw_obj *raw = &o->raw;
	struct mac_configuration_cmd *data =
		(struct mac_configuration_cmd *)(raw->rdata);
	int cnt = 0, i, rc;

	/* Reset the ramrod data buffer */
	ECORE_MEMSET(data, 0, sizeof(*data));

	/* First set all entries as invalid */
	for (i = 0; i < o->max_cmd_len ; i++)
		ECORE_SET_FLAG(data->config_table[i].flags,
			MAC_CONFIGURATION_ENTRY_ACTION_TYPE,
			T_ETH_MAC_COMMAND_INVALIDATE);

	/* Handle pending commands first */
	cnt = ecore_mcast_handle_pending_cmds_e1(sc, p);

	/* If there are no more pending commands - clear SCHEDULED state */
	if (ECORE_LIST_IS_EMPTY(&o->pending_cmds_head))
		o->clear_sched(o);

	/* The below may be TRUE iff there were no pending commands */
	if (!cnt)
		cnt = ecore_mcast_handle_current_cmd(sc, p, cmd, 0);

	/* For 57710 every command has o->max_cmd_len length to ensure that
	 * commands are done one at a time.
	 */
	o->total_pending_num -= o->max_cmd_len;

	/* send a ramrod */

	ECORE_DBG_BREAK_IF(cnt > o->max_cmd_len);

	/* Set ramrod header (in particular, a number of entries to update) */
	ecore_mcast_set_rdata_hdr_e1(sc, p, (uint8_t)cnt);

	/* update a registry: we need the registry contents to be always up
	 * to date in order to be able to execute a RESTORE opcode. Here
	 * we use the fact that for 57710 we sent one command at a time
	 * hence we may take the registry update out of the command handling
	 * and do it in a simpler way here.
	 */
	rc = ecore_mcast_refresh_registry_e1(sc, o);
	if (rc)
		return rc;

	/* If CLEAR_ONLY was requested - don't send a ramrod and clear
	 * RAMROD_PENDING status immediately.
	 */
	if (ECORE_TEST_BIT(RAMROD_DRV_CLR_ONLY, &p->ramrod_flags)) {
		raw->clear_pending(raw);
		return ECORE_SUCCESS;
	} else {
		/* No need for an explicit memory barrier here as long as we
		 * ensure the ordering of writing to the SPQ element
		 * and updating of the SPQ producer which involves a memory
		 * read. If the memory read is removed we will have to put a
		 * full memory barrier there (inside ecore_sp_post()).
		 */

		/* Send a ramrod */
		rc = ecore_sp_post( sc,
				    RAMROD_CMD_ID_ETH_SET_MAC,
				    raw->cid,
				    raw->rdata_mapping,
				    ETH_CONNECTION_TYPE);
		if (rc)
			return rc;

		/* Ramrod completion is pending */
		return ECORE_PENDING;
	}
}