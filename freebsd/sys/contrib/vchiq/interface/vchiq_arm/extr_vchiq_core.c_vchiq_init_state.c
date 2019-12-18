#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  threadname ;
typedef  int /*<<< orphan*/  VCHIQ_STATUS_T ;
struct TYPE_15__ {int id; int is_master; int slot_queue_available; int default_slot_quota; int previous_data_index; int data_quota; int /*<<< orphan*/ * sync_thread; int /*<<< orphan*/ * recycle_thread; int /*<<< orphan*/ * slot_handler_thread; int /*<<< orphan*/  sync_release_event; int /*<<< orphan*/  sync_trigger_event; int /*<<< orphan*/  recycle_event; int /*<<< orphan*/  trigger_event; scalar_t__ data_use_count; int /*<<< orphan*/  default_message_quota; int /*<<< orphan*/  slot_available_event; TYPE_4__* service_quotas; int /*<<< orphan*/  data_quota_event; int /*<<< orphan*/  slot_remove_event; int /*<<< orphan*/  bulk_transfer_mutex; int /*<<< orphan*/  sync_mutex; int /*<<< orphan*/  recycle_mutex; int /*<<< orphan*/  slot_mutex; int /*<<< orphan*/  mutex; int /*<<< orphan*/  connect; int /*<<< orphan*/ * slot_data; TYPE_3__* remote; TYPE_3__* local; } ;
typedef  TYPE_1__ VCHIQ_STATE_T ;
struct TYPE_14__ {int /*<<< orphan*/ * event; } ;
struct TYPE_17__ {int initialised; int slot_first; int slot_last; int* slot_queue; int slot_queue_recycle; int /*<<< orphan*/ * debug; TYPE_10__ sync_release; int /*<<< orphan*/  slot_sync; TYPE_10__ sync_trigger; TYPE_10__ recycle; scalar_t__ tx_pos; TYPE_10__ trigger; } ;
struct TYPE_16__ {scalar_t__ magic; scalar_t__ version; scalar_t__ version_min; int slot_zero_size; TYPE_3__ master; TYPE_3__ slave; int /*<<< orphan*/  max_slots_per_side; int /*<<< orphan*/  max_slots; int /*<<< orphan*/  slot_size; } ;
typedef  TYPE_2__ VCHIQ_SLOT_ZERO_T ;
typedef  int /*<<< orphan*/  VCHIQ_SLOT_T ;
typedef  TYPE_3__ VCHIQ_SHARED_STATE_T ;
struct TYPE_18__ {int /*<<< orphan*/  quota_event; } ;
typedef  TYPE_4__ VCHIQ_SERVICE_QUOTA_T ;
struct TYPE_19__ {int /*<<< orphan*/  msgid; } ;
typedef  TYPE_5__ VCHIQ_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 size_t DEBUG_ENTRIES ; 
 int /*<<< orphan*/  DEBUG_MAX ; 
 scalar_t__ SLOT_DATA_FROM_INDEX (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCHIQ_ERROR ; 
 scalar_t__ VCHIQ_MAGIC ; 
 int VCHIQ_MAX_SERVICES ; 
 int /*<<< orphan*/  VCHIQ_MAX_SLOTS ; 
 int /*<<< orphan*/  VCHIQ_MAX_SLOTS_PER_SIDE ; 
 int VCHIQ_MAX_STATES ; 
 int /*<<< orphan*/  VCHIQ_MSGID_PADDING ; 
 int /*<<< orphan*/  VCHIQ_SLOT_SIZE ; 
 scalar_t__ VCHIQ_VERSION ; 
 scalar_t__ VCHIQ_VERSION_MIN ; 
 int /*<<< orphan*/  _sema_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lmutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (unsigned short,unsigned short) ; 
 int /*<<< orphan*/  recycle_func ; 
 int /*<<< orphan*/  remote_event_create (TYPE_10__*) ; 
 int /*<<< orphan*/  remote_event_signal_local (TYPE_10__*) ; 
 int /*<<< orphan*/  set_user_nice (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  slot_handler_func ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  sync_func ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchiq_core_log_level ; 
 int /*<<< orphan*/  vchiq_log_warning (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vchiq_loud_error (char*,...) ; 
 int /*<<< orphan*/  vchiq_loud_error_footer () ; 
 int /*<<< orphan*/  vchiq_loud_error_header () ; 
 int /*<<< orphan*/  vchiq_platform_init_state (TYPE_1__*) ; 
 TYPE_1__** vchiq_states ; 
 void* vchiq_thread_create (int /*<<< orphan*/ *,void*,char*) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ *) ; 

VCHIQ_STATUS_T
vchiq_init_state(VCHIQ_STATE_T *state, VCHIQ_SLOT_ZERO_T *slot_zero,
		 int is_master)
{
	VCHIQ_SHARED_STATE_T *local;
	VCHIQ_SHARED_STATE_T *remote;
	VCHIQ_STATUS_T status;
	char threadname[10];
	static int id;
	int i;

	/* Check the input configuration */

	if (slot_zero->magic != VCHIQ_MAGIC) {
		vchiq_loud_error_header();
		vchiq_loud_error("Invalid VCHIQ magic value found.");
		vchiq_loud_error("slot_zero=%x: magic=%x (expected %x)",
			(unsigned int)slot_zero, slot_zero->magic, VCHIQ_MAGIC);
		vchiq_loud_error_footer();
		return VCHIQ_ERROR;
	}

	vchiq_log_warning(vchiq_core_log_level,
		"local ver %d (min %d), remote ver %d.",
		VCHIQ_VERSION, VCHIQ_VERSION_MIN,
		slot_zero->version);

	if (slot_zero->version < VCHIQ_VERSION_MIN) {
		vchiq_loud_error_header();
		vchiq_loud_error("Incompatible VCHIQ versions found.");
		vchiq_loud_error("slot_zero=%x: VideoCore version=%d "
			"(minimum %d)",
			(unsigned int)slot_zero, slot_zero->version,
			VCHIQ_VERSION_MIN);
		vchiq_loud_error("Restart with a newer VideoCore image.");
		vchiq_loud_error_footer();
		return VCHIQ_ERROR;
	}

	if (VCHIQ_VERSION < slot_zero->version_min) {
		vchiq_loud_error_header();
		vchiq_loud_error("Incompatible VCHIQ versions found.");
		vchiq_loud_error("slot_zero=%x: version=%d (VideoCore "
			"minimum %d)",
			(unsigned int)slot_zero, VCHIQ_VERSION,
			slot_zero->version_min);
		vchiq_loud_error("Restart with a newer kernel.");
		vchiq_loud_error_footer();
		return VCHIQ_ERROR;
	}

	if ((slot_zero->slot_zero_size != sizeof(VCHIQ_SLOT_ZERO_T)) ||
		 (slot_zero->slot_size != VCHIQ_SLOT_SIZE) ||
		 (slot_zero->max_slots != VCHIQ_MAX_SLOTS) ||
		 (slot_zero->max_slots_per_side != VCHIQ_MAX_SLOTS_PER_SIDE)) {
		vchiq_loud_error_header();
		if (slot_zero->slot_zero_size != sizeof(VCHIQ_SLOT_ZERO_T))
			vchiq_loud_error("slot_zero=%x: slot_zero_size=%x "
				"(expected %zx)",
				(unsigned int)slot_zero,
				slot_zero->slot_zero_size,
				sizeof(VCHIQ_SLOT_ZERO_T));
		if (slot_zero->slot_size != VCHIQ_SLOT_SIZE)
			vchiq_loud_error("slot_zero=%x: slot_size=%d "
				"(expected %d",
				(unsigned int)slot_zero, slot_zero->slot_size,
				VCHIQ_SLOT_SIZE);
		if (slot_zero->max_slots != VCHIQ_MAX_SLOTS)
			vchiq_loud_error("slot_zero=%x: max_slots=%d "
				"(expected %d)",
				(unsigned int)slot_zero, slot_zero->max_slots,
				VCHIQ_MAX_SLOTS);
		if (slot_zero->max_slots_per_side != VCHIQ_MAX_SLOTS_PER_SIDE)
			vchiq_loud_error("slot_zero=%x: max_slots_per_side=%d "
				"(expected %d)",
				(unsigned int)slot_zero,
				slot_zero->max_slots_per_side,
				VCHIQ_MAX_SLOTS_PER_SIDE);
		vchiq_loud_error_footer();
		return VCHIQ_ERROR;
	}

	if (VCHIQ_VERSION < slot_zero->version)
		slot_zero->version = VCHIQ_VERSION;

	if (is_master) {
		local = &slot_zero->master;
		remote = &slot_zero->slave;
	} else {
		local = &slot_zero->slave;
		remote = &slot_zero->master;
	}

	if (local->initialised) {
		vchiq_loud_error_header();
		if (remote->initialised)
			vchiq_loud_error("local state has already been "
				"initialised");
		else
			vchiq_loud_error("master/slave mismatch - two %ss",
				is_master ? "master" : "slave");
		vchiq_loud_error_footer();
		return VCHIQ_ERROR;
	}

	memset(state, 0, sizeof(VCHIQ_STATE_T));

	state->id = id++;
	state->is_master = is_master;

	/*
		initialize shared state pointers
	 */

	state->local = local;
	state->remote = remote;
	state->slot_data = (VCHIQ_SLOT_T *)slot_zero;

	/*
		initialize events and mutexes
	 */

	_sema_init(&state->connect, 0);
	lmutex_init(&state->mutex);
	_sema_init(&state->trigger_event, 0);
	_sema_init(&state->recycle_event, 0);
	_sema_init(&state->sync_trigger_event, 0);
	_sema_init(&state->sync_release_event, 0);

	lmutex_init(&state->slot_mutex);
	lmutex_init(&state->recycle_mutex);
	lmutex_init(&state->sync_mutex);
	lmutex_init(&state->bulk_transfer_mutex);

	_sema_init(&state->slot_available_event, 0);
	_sema_init(&state->slot_remove_event, 0);
	_sema_init(&state->data_quota_event, 0);

	state->slot_queue_available = 0;

	for (i = 0; i < VCHIQ_MAX_SERVICES; i++) {
		VCHIQ_SERVICE_QUOTA_T *service_quota =
			&state->service_quotas[i];
		_sema_init(&service_quota->quota_event, 0);
	}

	for (i = local->slot_first; i <= local->slot_last; i++) {
		local->slot_queue[state->slot_queue_available++] = i;
		up(&state->slot_available_event);
	}

	state->default_slot_quota = state->slot_queue_available/2;
	state->default_message_quota =
		min((unsigned short)(state->default_slot_quota * 256),
		(unsigned short)~0);

	state->previous_data_index = -1;
	state->data_use_count = 0;
	state->data_quota = state->slot_queue_available - 1;

	local->trigger.event = &state->trigger_event;
	remote_event_create(&local->trigger);
	local->tx_pos = 0;

	local->recycle.event = &state->recycle_event;
	remote_event_create(&local->recycle);
	local->slot_queue_recycle = state->slot_queue_available;

	local->sync_trigger.event = &state->sync_trigger_event;
	remote_event_create(&local->sync_trigger);

	local->sync_release.event = &state->sync_release_event;
	remote_event_create(&local->sync_release);

	/* At start-of-day, the slot is empty and available */
	((VCHIQ_HEADER_T *)SLOT_DATA_FROM_INDEX(state, local->slot_sync))->msgid
		= VCHIQ_MSGID_PADDING;
	remote_event_signal_local(&local->sync_release);

	local->debug[DEBUG_ENTRIES] = DEBUG_MAX;

	status = vchiq_platform_init_state(state);

	/*
		bring up slot handler thread
	 */
	snprintf(threadname, sizeof(threadname), "VCHIQ-%d", state->id);
	state->slot_handler_thread = vchiq_thread_create(&slot_handler_func,
		(void *)state,
		threadname);

	if (state->slot_handler_thread == NULL) {
		vchiq_loud_error_header();
		vchiq_loud_error("couldn't create thread %s", threadname);
		vchiq_loud_error_footer();
		return VCHIQ_ERROR;
	}
	set_user_nice(state->slot_handler_thread, -19);
	wake_up_process(state->slot_handler_thread);

	snprintf(threadname, sizeof(threadname), "VCHIQr-%d", state->id);
	state->recycle_thread = vchiq_thread_create(&recycle_func,
		(void *)state,
		threadname);
	if (state->recycle_thread == NULL) {
		vchiq_loud_error_header();
		vchiq_loud_error("couldn't create thread %s", threadname);
		vchiq_loud_error_footer();
		return VCHIQ_ERROR;
	}
	set_user_nice(state->recycle_thread, -19);
	wake_up_process(state->recycle_thread);

	snprintf(threadname, sizeof(threadname), "VCHIQs-%d", state->id);
	state->sync_thread = vchiq_thread_create(&sync_func,
		(void *)state,
		threadname);
	if (state->sync_thread == NULL) {
		vchiq_loud_error_header();
		vchiq_loud_error("couldn't create thread %s", threadname);
		vchiq_loud_error_footer();
		return VCHIQ_ERROR;
	}
	set_user_nice(state->sync_thread, -20);
	wake_up_process(state->sync_thread);

	BUG_ON(state->id >= VCHIQ_MAX_STATES);
	vchiq_states[state->id] = state;

	/* Indicate readiness to the other side */
	local->initialised = 1;

	return status;
}