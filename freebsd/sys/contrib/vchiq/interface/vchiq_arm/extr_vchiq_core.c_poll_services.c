#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_11__ {int /*<<< orphan*/  id; int /*<<< orphan*/ * poll_services; int /*<<< orphan*/  unused_service; } ;
typedef  TYPE_1__ VCHIQ_STATE_T ;
struct TYPE_12__ {int /*<<< orphan*/  bulk_rx; int /*<<< orphan*/  bulk_tx; int /*<<< orphan*/  remoteport; int /*<<< orphan*/  localport; int /*<<< orphan*/  public_fourcc; int /*<<< orphan*/  poll_flags; } ;
typedef  TYPE_2__ VCHIQ_SERVICE_T ;

/* Variables and functions */
 int BITSET_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCHIQ_FOURCC_INVALID ; 
 int VCHIQ_POLL_REMOVE ; 
 int VCHIQ_POLL_RXNOTIFY ; 
 int VCHIQ_POLL_TERMINATE ; 
 int VCHIQ_POLL_TXNOTIFY ; 
 scalar_t__ VCHIQ_SUCCESS ; 
 int atomic_xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* find_service_by_port (TYPE_1__*,int) ; 
 int /*<<< orphan*/  notify_bulks (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  request_poll (TYPE_1__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  unlock_service (TYPE_2__*) ; 
 scalar_t__ vchiq_close_service_internal (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_core_log_level ; 
 int /*<<< orphan*/  vchiq_log_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
poll_services(VCHIQ_STATE_T *state)
{
	int group, i;

	for (group = 0; group < BITSET_SIZE(state->unused_service); group++) {
		uint32_t flags;
		flags = atomic_xchg(&state->poll_services[group], 0);
		for (i = 0; flags; i++) {
			if (flags & (1 << i)) {
				VCHIQ_SERVICE_T *service =
					find_service_by_port(state,
						(group<<5) + i);
				uint32_t service_flags;
				flags &= ~(1 << i);
				if (!service)
					continue;
				service_flags =
					atomic_xchg(&service->poll_flags, 0);
				if (service_flags &
					(1 << VCHIQ_POLL_REMOVE)) {
					vchiq_log_info(vchiq_core_log_level,
						"%d: ps - remove %d<->%d",
						state->id, service->localport,
						service->remoteport);

					/* Make it look like a client, because
					   it must be removed and not left in
					   the LISTENING state. */
					service->public_fourcc =
						VCHIQ_FOURCC_INVALID;

					if (vchiq_close_service_internal(
						service, 0/*!close_recvd*/) !=
						VCHIQ_SUCCESS)
						request_poll(state, service,
							VCHIQ_POLL_REMOVE);
				} else if (service_flags &
					(1 << VCHIQ_POLL_TERMINATE)) {
					vchiq_log_info(vchiq_core_log_level,
						"%d: ps - terminate %d<->%d",
						state->id, service->localport,
						service->remoteport);
					if (vchiq_close_service_internal(
						service, 0/*!close_recvd*/) !=
						VCHIQ_SUCCESS)
						request_poll(state, service,
							VCHIQ_POLL_TERMINATE);
				}
				if (service_flags & (1 << VCHIQ_POLL_TXNOTIFY))
					notify_bulks(service,
						&service->bulk_tx,
						1/*retry_poll*/);
				if (service_flags & (1 << VCHIQ_POLL_RXNOTIFY))
					notify_bulks(service,
						&service->bulk_rx,
						1/*retry_poll*/);
				unlock_service(service);
			}
		}
	}
}