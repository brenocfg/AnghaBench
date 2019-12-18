#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_48__   TYPE_4__ ;
typedef  struct TYPE_47__   TYPE_3__ ;
typedef  struct TYPE_46__   TYPE_2__ ;
typedef  struct TYPE_45__   TYPE_28__ ;
typedef  struct TYPE_44__   TYPE_24__ ;
typedef  struct TYPE_43__   TYPE_21__ ;
typedef  struct TYPE_42__   TYPE_1__ ;

/* Type definitions */
struct TYPE_43__ {int /*<<< orphan*/  cache_valid; } ;
struct TYPE_47__ {TYPE_24__* p_subn; int /*<<< orphan*/  subnet_up_event; int /*<<< orphan*/  p_log; TYPE_21__ ucast_mgr; int /*<<< orphan*/  lid_mgr; scalar_t__ polling_sm_guid; int /*<<< orphan*/  p_lock; scalar_t__ master_sm_found; } ;
typedef  TYPE_3__ osm_sm_t ;
struct TYPE_42__ {scalar_t__ guid; } ;
struct TYPE_48__ {TYPE_1__ smi; } ;
typedef  TYPE_4__ osm_remote_sm_t ;
typedef  scalar_t__ ib_api_status_t ;
struct TYPE_46__ {scalar_t__ force_heavy_sweep; int /*<<< orphan*/  fsync_high_avail_files; scalar_t__ sa_db_dump; int /*<<< orphan*/  disable_multicast; scalar_t__ use_ucast_cache; } ;
struct TYPE_45__ {int /*<<< orphan*/  stats; } ;
struct TYPE_44__ {scalar_t__ force_heavy_sweep; scalar_t__ subnet_initialization_error; scalar_t__ sm_state; int need_update; scalar_t__ force_reroute; int last_sm_port_state; TYPE_28__* p_osm; TYPE_2__ opt; int /*<<< orphan*/  p_neighbor; int /*<<< orphan*/  p_g2m; scalar_t__ first_time_master_sweep; scalar_t__ coming_out_of_standby; int /*<<< orphan*/  sw_guid_tbl; scalar_t__ ignore_existing_lfts; void* min_sw_data_vls; void* min_data_vls; int /*<<< orphan*/  min_ca_rate; int /*<<< orphan*/  min_ca_mtu; scalar_t__ force_first_time_master_sweep; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_PLOCK_EXCL_ACQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CL_PLOCK_RELEASE (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FILE_ID ; 
 int /*<<< orphan*/  IB_LINK_ACTIVE ; 
 int /*<<< orphan*/  IB_LINK_ARMED ; 
 int /*<<< orphan*/  IB_LINK_NO_CHANGE ; 
 int /*<<< orphan*/  IB_MAX_MTU ; 
 void* IB_MAX_NUM_VLS ; 
 int /*<<< orphan*/  IB_PATH_RECORD_RATE_300_GBS ; 
 scalar_t__ IB_SMINFO_STATE_DISCOVERING ; 
 scalar_t__ IB_SMINFO_STATE_MASTER ; 
 scalar_t__ IB_SUCCESS ; 
 int /*<<< orphan*/  OSM_EVENT_ID_HEAVY_SWEEP_DONE ; 
 int /*<<< orphan*/  OSM_EVENT_ID_HEAVY_SWEEP_START ; 
 int /*<<< orphan*/  OSM_EVENT_ID_SA_DB_DUMPED ; 
 int /*<<< orphan*/  OSM_EVENT_ID_STATE_CHANGE ; 
 int /*<<< orphan*/  OSM_EVENT_ID_SUBNET_UP ; 
 int /*<<< orphan*/  OSM_EVENT_ID_UCAST_ROUTING_DONE ; 
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OSM_LOG_ERROR ; 
 scalar_t__ OSM_LOG_IS_ACTIVE_V2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSM_LOG_MSG_BOX (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OSM_LOG_SYS ; 
 int /*<<< orphan*/  OSM_LOG_VERBOSE ; 
 int /*<<< orphan*/  OSM_SIGNAL_SWEEP ; 
 int /*<<< orphan*/  OSM_SM_SIGNAL_DISCOVER ; 
 int /*<<< orphan*/  OSM_SM_SIGNAL_DISCOVERY_COMPLETED ; 
 int /*<<< orphan*/  OSM_SM_SIGNAL_HANDOVER_SENT ; 
 int /*<<< orphan*/  OSM_SM_SIGNAL_MASTER_OR_HIGHER_SM_DETECTED ; 
 int /*<<< orphan*/  OSM_SM_SIGNAL_POLLING_TIMEOUT ; 
 int /*<<< orphan*/  OSM_SM_SIGNAL_WAIT_FOR_HANDOVER ; 
 scalar_t__ TRUE ; 
 scalar_t__ UCAST_ROUTING_HEAVY_SWEEP ; 
 scalar_t__ UCAST_ROUTING_REROUTE ; 
 int /*<<< orphan*/  check_switch_lft ; 
 int /*<<< orphan*/  cl_event_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_qmap_apply_func (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cl_qmap_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osm_congestion_control_setup (TYPE_28__*) ; 
 scalar_t__ osm_congestion_control_wait_pending_transactions (TYPE_28__*) ; 
 int /*<<< orphan*/  osm_db_store (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osm_drop_mgr_process (TYPE_3__*) ; 
 int /*<<< orphan*/  osm_dump_all (TYPE_28__*) ; 
 int /*<<< orphan*/  osm_guid_mgr_process (TYPE_3__*) ; 
 int /*<<< orphan*/  osm_lid_mgr_process_sm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osm_lid_mgr_process_subnet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osm_link_mgr_process (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osm_log_v2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  osm_mcast_mgr_process (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  osm_opensm_report_event (TYPE_28__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  osm_pkey_mgr_process (TYPE_28__*) ; 
 int /*<<< orphan*/  osm_qos_setup (TYPE_28__*) ; 
 int /*<<< orphan*/  osm_reset_switch_state_change_bit (TYPE_28__*) ; 
 int /*<<< orphan*/  osm_sa_db_file_dump (TYPE_28__*) ; 
 int /*<<< orphan*/  osm_sa_db_file_load (TYPE_28__*) ; 
 int /*<<< orphan*/  osm_send_trap144 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osm_sm_signal (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osm_sm_state_mgr_process (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ osm_subn_rescan_conf_files (TYPE_24__*) ; 
 int /*<<< orphan*/  osm_ucast_cache_invalidate (TYPE_21__*) ; 
 scalar_t__ osm_ucast_cache_process (TYPE_21__*) ; 
 scalar_t__ osm_ucast_mgr_process (TYPE_21__*) ; 
 int /*<<< orphan*/  state_mgr_check_tbl_consistency (TYPE_3__*) ; 
 int /*<<< orphan*/  state_mgr_clean_known_lids (TYPE_3__*) ; 
 TYPE_4__* state_mgr_exists_other_master_sm (TYPE_3__*) ; 
 TYPE_4__* state_mgr_get_highest_sm (TYPE_3__*) ; 
 scalar_t__ state_mgr_is_sm_port_down (TYPE_3__*) ; 
 scalar_t__ state_mgr_light_sweep_start (TYPE_3__*) ; 
 int /*<<< orphan*/  state_mgr_notify_lid_change (TYPE_3__*) ; 
 int /*<<< orphan*/  state_mgr_report_new_ports (TYPE_3__*) ; 
 int /*<<< orphan*/  state_mgr_sa_clean (TYPE_3__*) ; 
 int /*<<< orphan*/  state_mgr_send_handover (TYPE_3__*,TYPE_4__*) ; 
 scalar_t__ state_mgr_sweep_hop_0 (TYPE_3__*) ; 
 scalar_t__ state_mgr_sweep_hop_1 (TYPE_3__*) ; 
 int /*<<< orphan*/  state_mgr_up_msg (TYPE_3__*) ; 
 scalar_t__ wait_for_pending_transactions (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_sweep(osm_sm_t * sm)
{
	ib_api_status_t status;
	osm_remote_sm_t *p_remote_sm;
	unsigned config_parsed = 0;

	if (sm->p_subn->force_first_time_master_sweep) {
		sm->p_subn->force_heavy_sweep = TRUE;
		sm->p_subn->coming_out_of_standby = TRUE;
		sm->p_subn->first_time_master_sweep = TRUE;
		sm->p_subn->force_first_time_master_sweep = FALSE;
	}

	/* after subnet initialization error, run heavy sweep */
	if (sm->p_subn->subnet_initialization_error)
		sm->p_subn->force_heavy_sweep = TRUE;

	if (sm->p_subn->force_heavy_sweep) {
		if (osm_subn_rescan_conf_files(sm->p_subn) < 0)
			OSM_LOG(sm->p_log, OSM_LOG_ERROR, "ERR 331A: "
				"osm_subn_rescan_conf_file failed\n");
		else
			config_parsed = 1;
	}

	if (sm->p_subn->sm_state != IB_SMINFO_STATE_MASTER &&
	    sm->p_subn->sm_state != IB_SMINFO_STATE_DISCOVERING)
		return;

	if (sm->p_subn->coming_out_of_standby) {
		/*
		 * Need to force re-write of sm_base_lid to all ports
		 * to do that we want all the ports to be considered
		 * foreign
		 */
		state_mgr_clean_known_lids(sm);

		/*
		 * Need to clean SA cache when state changes to STANDBY
		 * after handover.
		 */
		state_mgr_sa_clean(sm);

		/*
		 * Need to reconfigure LFTs, PKEYs, and QoS on all switches
		 * when coming out of STANDBY
		 */
		sm->p_subn->need_update = 1;
	}

	sm->master_sm_found = 0;

	/*
	 * If we already have switches, then try a light sweep.
	 * Otherwise, this is probably our first discovery pass
	 * or we are connected in loopback. In both cases do a
	 * heavy sweep.
	 * Note: If we are connected in loopback we want a heavy
	 * sweep, since we will not be getting any traps if there is
	 * a lost connection.
	 */
	/*  if we are in DISCOVERING state - this means it is either in
	 *  initializing or wake up from STANDBY - run the heavy sweep */
	if (cl_qmap_count(&sm->p_subn->sw_guid_tbl)
	    && sm->p_subn->sm_state != IB_SMINFO_STATE_DISCOVERING
	    && sm->p_subn->opt.force_heavy_sweep == FALSE
	    && sm->p_subn->force_heavy_sweep == FALSE
	    && sm->p_subn->force_reroute == FALSE
	    && sm->p_subn->subnet_initialization_error == FALSE
	    && (state_mgr_light_sweep_start(sm) == IB_SUCCESS)) {
		if (wait_for_pending_transactions(&sm->p_subn->p_osm->stats))
			return;
		if (!sm->p_subn->force_heavy_sweep) {
			if (sm->p_subn->opt.sa_db_dump &&
			    !osm_sa_db_file_dump(sm->p_subn->p_osm))
				osm_opensm_report_event(sm->p_subn->p_osm,
							OSM_EVENT_ID_SA_DB_DUMPED,
							NULL);
			OSM_LOG_MSG_BOX(sm->p_log, OSM_LOG_VERBOSE,
					"LIGHT SWEEP COMPLETE");
			return;
		}
	}

	/*
	 * Unicast cache should be invalidated when subnet re-route is
	 * requested, and when OpenSM comes out of standby state.
	 */
	if (sm->p_subn->opt.use_ucast_cache &&
	    (sm->p_subn->force_reroute || sm->p_subn->coming_out_of_standby))
		osm_ucast_cache_invalidate(&sm->ucast_mgr);

	/*
	 * If we don't need to do a heavy sweep and we want to do a reroute,
	 * just reroute only.
	 */
	if (cl_qmap_count(&sm->p_subn->sw_guid_tbl)
	    && sm->p_subn->sm_state != IB_SMINFO_STATE_DISCOVERING
	    && sm->p_subn->opt.force_heavy_sweep == FALSE
	    && sm->p_subn->force_heavy_sweep == FALSE
	    && sm->p_subn->force_reroute == TRUE
	    && sm->p_subn->subnet_initialization_error == FALSE) {
		/* Reset flag */
		sm->p_subn->force_reroute = FALSE;

		/* Re-program the switches fully */
		sm->p_subn->ignore_existing_lfts = TRUE;

		if (osm_ucast_mgr_process(&sm->ucast_mgr)) {
			OSM_LOG_MSG_BOX(sm->p_log, OSM_LOG_VERBOSE,
					"REROUTE FAILED");
			return;
		}
		osm_qos_setup(sm->p_subn->p_osm);

		/* Reset flag */
		sm->p_subn->ignore_existing_lfts = FALSE;

		if (wait_for_pending_transactions(&sm->p_subn->p_osm->stats))
			return;

		osm_congestion_control_setup(sm->p_subn->p_osm);

		if (osm_congestion_control_wait_pending_transactions(sm->p_subn->p_osm))
			return;

		if (!sm->p_subn->subnet_initialization_error) {
			OSM_LOG_MSG_BOX(sm->p_log, OSM_LOG_VERBOSE,
					"REROUTE COMPLETE");
			osm_opensm_report_event(sm->p_subn->p_osm,
						OSM_EVENT_ID_UCAST_ROUTING_DONE,
						(void *) UCAST_ROUTING_REROUTE);
			return;
		}
	}

	osm_opensm_report_event(sm->p_subn->p_osm,
				OSM_EVENT_ID_HEAVY_SWEEP_START, NULL);

	/* go to heavy sweep */
repeat_discovery:

	/* First of all - unset all flags */
	sm->p_subn->force_heavy_sweep = FALSE;
	sm->p_subn->force_reroute = FALSE;
	sm->p_subn->subnet_initialization_error = FALSE;

	/* Reset tracking values in case limiting component got removed
	 * from fabric. */
	sm->p_subn->min_ca_mtu = IB_MAX_MTU;
	sm->p_subn->min_ca_rate = IB_PATH_RECORD_RATE_300_GBS;
	sm->p_subn->min_data_vls = IB_MAX_NUM_VLS - 1;
	sm->p_subn->min_sw_data_vls = IB_MAX_NUM_VLS - 1;

	/* rescan configuration updates */
	if (!config_parsed && osm_subn_rescan_conf_files(sm->p_subn) < 0)
		OSM_LOG(sm->p_log, OSM_LOG_ERROR, "ERR 331A: "
			"osm_subn_rescan_conf_file failed\n");

	if (sm->p_subn->sm_state != IB_SMINFO_STATE_MASTER)
		sm->p_subn->need_update = 1;

	status = state_mgr_sweep_hop_0(sm);
	if (status != IB_SUCCESS ||
	    wait_for_pending_transactions(&sm->p_subn->p_osm->stats))
		return;

	if (state_mgr_is_sm_port_down(sm) == TRUE) {
		if (sm->p_subn->last_sm_port_state) {
			sm->p_subn->last_sm_port_state = 0;
			state_mgr_sa_clean(sm);
			osm_log_v2(sm->p_log, OSM_LOG_SYS, FILE_ID,
				   "SM port is down\n");
			OSM_LOG_MSG_BOX(sm->p_log, OSM_LOG_VERBOSE,
					"SM PORT DOWN");
		}

		/* Run the drop manager - we want to clear all records */
		osm_drop_mgr_process(sm);

		/* Move to DISCOVERING state */
		if (sm->p_subn->sm_state != IB_SMINFO_STATE_DISCOVERING)
			osm_sm_state_mgr_process(sm, OSM_SM_SIGNAL_DISCOVER);
		osm_opensm_report_event(sm->p_subn->p_osm,
					OSM_EVENT_ID_STATE_CHANGE, NULL);
		return;
	} else {
		if (!sm->p_subn->last_sm_port_state) {
			sm->p_subn->last_sm_port_state = 1;
			osm_log_v2(sm->p_log, OSM_LOG_SYS, FILE_ID,
				   "SM port is up\n");
			OSM_LOG_MSG_BOX(sm->p_log, OSM_LOG_VERBOSE,
					"SM PORT UP");
		}
	}

	status = state_mgr_sweep_hop_1(sm);
	if (status != IB_SUCCESS ||
	    wait_for_pending_transactions(&sm->p_subn->p_osm->stats))
		return;

	/* discovery completed - check other sm presence */
	if (sm->master_sm_found) {
		/*
		 * Call the sm_state_mgr with signal
		 * MASTER_OR_HIGHER_SM_DETECTED_DONE
		 */
		osm_sm_state_mgr_process(sm,
					 OSM_SM_SIGNAL_MASTER_OR_HIGHER_SM_DETECTED);
		OSM_LOG_MSG_BOX(sm->p_log, OSM_LOG_VERBOSE,
				"ENTERING STANDBY STATE");
		/* notify master SM about us */
		osm_send_trap144(sm, 0);
		osm_opensm_report_event(sm->p_subn->p_osm,
					OSM_EVENT_ID_STATE_CHANGE, NULL);
		return;
	}

	/* if new sweep requested - don't bother with the rest */
	if (sm->p_subn->force_heavy_sweep) {
		config_parsed = 0;
		goto repeat_discovery;
	}

	osm_opensm_report_event(sm->p_subn->p_osm,
				OSM_EVENT_ID_HEAVY_SWEEP_DONE, NULL);

	OSM_LOG_MSG_BOX(sm->p_log, OSM_LOG_VERBOSE, "HEAVY SWEEP COMPLETE");

	osm_drop_mgr_process(sm);

	/* If we are MASTER - get the highest remote_sm, and
	 * see if it is higher than our local sm.
	 */
	if (sm->p_subn->sm_state == IB_SMINFO_STATE_MASTER) {
		p_remote_sm = state_mgr_get_highest_sm(sm);
		if (p_remote_sm != NULL) {
			/* report new ports (trap 64) before leaving MASTER */
			state_mgr_report_new_ports(sm);

			/* need to handover the mastership
			 * to the remote sm, and move to standby */
			state_mgr_send_handover(sm, p_remote_sm);
			osm_sm_state_mgr_process(sm,
						 OSM_SM_SIGNAL_HANDOVER_SENT);
			return;
		} else {
			/* We are the highest sm - check to see if there is
			 * a remote SM that is in master state. */
			p_remote_sm = state_mgr_exists_other_master_sm(sm);
			if (p_remote_sm != NULL) {
				/* There is a remote SM that is master.
				 * need to wait for that SM to relinquish control
				 * of its portion of the subnet. C14-60.2.1.
				 * Also - need to start polling on that SM. */
				CL_PLOCK_EXCL_ACQUIRE(sm->p_lock);
				sm->polling_sm_guid = p_remote_sm->smi.guid;
				CL_PLOCK_RELEASE(sm->p_lock);
				osm_sm_state_mgr_process(sm,
							 OSM_SM_SIGNAL_WAIT_FOR_HANDOVER);
				return;
			} else if (sm->polling_sm_guid) {
				/* Stop polling SM if it's not found */
				osm_sm_state_mgr_process(sm,
							 OSM_SM_SIGNAL_POLLING_TIMEOUT);
				return;
			}
		}
	}

	/*
	 * If we are not MASTER already - this means that we are
	 * in discovery state. call osm_sm_state_mgr with signal
	 * DISCOVERY_COMPLETED
	 */
	if (sm->p_subn->sm_state == IB_SMINFO_STATE_DISCOVERING)
		osm_sm_state_mgr_process(sm, OSM_SM_SIGNAL_DISCOVERY_COMPLETED);

	osm_reset_switch_state_change_bit(sm->p_subn->p_osm);
	if (wait_for_pending_transactions(&sm->p_subn->p_osm->stats))
		return;

	osm_pkey_mgr_process(sm->p_subn->p_osm);

	/* try to restore SA DB (this should be before lid_mgr
	   because we may want to disable clients reregistration
	   when SA DB is restored) */
	osm_sa_db_file_load(sm->p_subn->p_osm);

	if (wait_for_pending_transactions(&sm->p_subn->p_osm->stats))
		return;

	OSM_LOG_MSG_BOX(sm->p_log, OSM_LOG_VERBOSE,
			"PKEY setup completed - STARTING SM LID CONFIG");

	osm_lid_mgr_process_sm(&sm->lid_mgr);
	if (wait_for_pending_transactions(&sm->p_subn->p_osm->stats))
		return;

	OSM_LOG_MSG_BOX(sm->p_log, OSM_LOG_VERBOSE,
			"SM LID ASSIGNMENT COMPLETE - STARTING SUBNET LID CONFIG");
	state_mgr_notify_lid_change(sm);

	osm_lid_mgr_process_subnet(&sm->lid_mgr);
	if (wait_for_pending_transactions(&sm->p_subn->p_osm->stats))
		return;

	/* At this point we need to check the consistency of
	 * the port_lid_tbl under the subnet. There might be
	 * errors in it if PortInfo Set requests didn't reach
	 * their destination. */
	state_mgr_check_tbl_consistency(sm);

	OSM_LOG_MSG_BOX(sm->p_log, OSM_LOG_VERBOSE,
			"LID ASSIGNMENT COMPLETE - STARTING SWITCH TABLE CONFIG");

	/*
	 * Proceed with unicast forwarding table configuration; if it fails
	 * return early to wait for a trap or the next sweep interval.
	 */

	if (!sm->ucast_mgr.cache_valid ||
	    osm_ucast_cache_process(&sm->ucast_mgr)) {
		if (osm_ucast_mgr_process(&sm->ucast_mgr)) {
			osm_ucast_cache_invalidate(&sm->ucast_mgr);
			return;
		}
	}

	osm_qos_setup(sm->p_subn->p_osm);

	if (wait_for_pending_transactions(&sm->p_subn->p_osm->stats))
		return;

	/* We are done setting all LFTs so clear the ignore existing.
	 * From now on, as long as we are still master, we want to
	 * take into account these lfts. */
	sm->p_subn->ignore_existing_lfts = FALSE;

	OSM_LOG_MSG_BOX(sm->p_log, OSM_LOG_VERBOSE,
			"SWITCHES CONFIGURED FOR UNICAST");
	osm_opensm_report_event(sm->p_subn->p_osm,
				OSM_EVENT_ID_UCAST_ROUTING_DONE,
				(void *) UCAST_ROUTING_HEAVY_SWEEP);

	if (!sm->p_subn->opt.disable_multicast) {
		osm_mcast_mgr_process(sm, TRUE);
		if (wait_for_pending_transactions(&sm->p_subn->p_osm->stats))
			return;
		OSM_LOG_MSG_BOX(sm->p_log, OSM_LOG_VERBOSE,
				"SWITCHES CONFIGURED FOR MULTICAST");
	}

	osm_guid_mgr_process(sm);
	if (wait_for_pending_transactions(&sm->p_subn->p_osm->stats))
		return;
	OSM_LOG_MSG_BOX(sm->p_log, OSM_LOG_VERBOSE, "ALIAS GUIDS CONFIGURED");

	/*
	 * The LINK_PORTS state is required since we cannot count on
	 * the port state change MADs to succeed. This is an artifact
	 * of the spec defining state change from state X to state X
	 * as an error. The hardware then is not required to process
	 * other parameters provided by the Set(PortInfo) Packet.
	 */

	osm_link_mgr_process(sm, IB_LINK_NO_CHANGE);
	if (wait_for_pending_transactions(&sm->p_subn->p_osm->stats))
		return;

	OSM_LOG_MSG_BOX(sm->p_log, OSM_LOG_VERBOSE,
			"LINKS PORTS CONFIGURED - SET LINKS TO ARMED STATE");

	osm_link_mgr_process(sm, IB_LINK_ARMED);
	if (wait_for_pending_transactions(&sm->p_subn->p_osm->stats))
		return;

	OSM_LOG_MSG_BOX(sm->p_log, OSM_LOG_VERBOSE,
			"LINKS ARMED - SET LINKS TO ACTIVE STATE");

	osm_link_mgr_process(sm, IB_LINK_ACTIVE);
	if (wait_for_pending_transactions(&sm->p_subn->p_osm->stats))
		return;

	/*
	 * The sweep completed!
	 */

	/* Now do GSI configuration */

	osm_congestion_control_setup(sm->p_subn->p_osm);

	if (osm_congestion_control_wait_pending_transactions(sm->p_subn->p_osm))
		return;

	/*
	 * Send trap 64 on newly discovered endports
	 */
	state_mgr_report_new_ports(sm);

	/* check switch lft buffers assignments */
	cl_qmap_apply_func(&sm->p_subn->sw_guid_tbl, check_switch_lft,
			   sm->p_log);

	/* in any case we zero this flag */
	sm->p_subn->coming_out_of_standby = FALSE;
	sm->p_subn->first_time_master_sweep = FALSE;

	/* If there were errors - then the subnet is not really up */
	if (sm->p_subn->subnet_initialization_error == TRUE) {
		osm_log_v2(sm->p_log, OSM_LOG_SYS, FILE_ID,
			   "Errors during initialization\n");
		OSM_LOG_MSG_BOX(sm->p_log, OSM_LOG_ERROR,
				"ERRORS DURING INITIALIZATION");
	} else {
		sm->p_subn->need_update = 0;
		osm_dump_all(sm->p_subn->p_osm);
		state_mgr_up_msg(sm);

		if ((OSM_LOG_IS_ACTIVE_V2(sm->p_log, OSM_LOG_VERBOSE) ||
		    sm->p_subn->opt.sa_db_dump) &&
		    !osm_sa_db_file_dump(sm->p_subn->p_osm))
			osm_opensm_report_event(sm->p_subn->p_osm,
						OSM_EVENT_ID_SA_DB_DUMPED,
						NULL);
	}

	/*
	 * Finally signal the subnet up event
	 */
	cl_event_signal(&sm->subnet_up_event);

	/* if we got a signal to force heavy sweep or errors
	 * in the middle of the sweep - try another sweep. */
	if (sm->p_subn->force_heavy_sweep)
		osm_sm_signal(sm, OSM_SIGNAL_SWEEP);

	/* Write a new copy of our persistent guid2mkey database */
	osm_db_store(sm->p_subn->p_g2m, sm->p_subn->opt.fsync_high_avail_files);
	osm_db_store(sm->p_subn->p_neighbor,
		     sm->p_subn->opt.fsync_high_avail_files);

	osm_opensm_report_event(sm->p_subn->p_osm, OSM_EVENT_ID_SUBNET_UP,
				NULL);
}