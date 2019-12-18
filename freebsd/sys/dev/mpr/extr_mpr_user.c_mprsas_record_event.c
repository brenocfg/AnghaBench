#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct mpr_softc {int* events_to_record; int event_index; TYPE_1__* recorded_events; scalar_t__ event_number; } ;
typedef  scalar_t__ boolean_t ;
struct TYPE_5__ {int Event; int EventDataLength; int /*<<< orphan*/ * EventData; } ;
struct TYPE_4__ {int Type; int /*<<< orphan*/ * Data; scalar_t__ Number; } ;
typedef  TYPE_2__ MPI2_EVENT_NOTIFICATION_REPLY ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int MPI2_EVENT_LOG_ENTRY_ADDED ; 
 int MPR_EVENT_QUEUE_SIZE ; 
 int MPR_MAX_EVENT_DATA_LENGTH ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 

void
mprsas_record_event(struct mpr_softc *sc,
    MPI2_EVENT_NOTIFICATION_REPLY *event_reply)
{
	uint32_t	event;
	int		i, j;
	uint16_t	event_data_len;
	boolean_t	sendAEN = FALSE;

	event = event_reply->Event;

	/*
	 * Generate a system event to let anyone who cares know that a
	 * LOG_ENTRY_ADDED event has occurred.  This is sent no matter what the
	 * event mask is set to.
	 */
	if (event == MPI2_EVENT_LOG_ENTRY_ADDED) {
		sendAEN = TRUE;
	}

	/*
	 * Record the event only if its corresponding bit is set in
	 * events_to_record.  event_index is the index into recorded_events and
	 * event_number is the overall number of an event being recorded since
	 * start-of-day.  event_index will roll over; event_number will never
	 * roll over.
	 */
	i = (uint8_t)(event / 32);
	j = (uint8_t)(event % 32);
	if ((i < 4) && ((1 << j) & sc->events_to_record[i])) {
		i = sc->event_index;
		sc->recorded_events[i].Type = event;
		sc->recorded_events[i].Number = ++sc->event_number;
		bzero(sc->recorded_events[i].Data, MPR_MAX_EVENT_DATA_LENGTH *
		    4);
		event_data_len = event_reply->EventDataLength;

		if (event_data_len > 0) {
			/*
			 * Limit data to size in m_event entry
			 */
			if (event_data_len > MPR_MAX_EVENT_DATA_LENGTH) {
				event_data_len = MPR_MAX_EVENT_DATA_LENGTH;
			}
			for (j = 0; j < event_data_len; j++) {
				sc->recorded_events[i].Data[j] =
				    event_reply->EventData[j];
			}

			/*
			 * check for index wrap-around
			 */
			if (++i == MPR_EVENT_QUEUE_SIZE) {
				i = 0;
			}
			sc->event_index = (uint8_t)i;

			/*
			 * Set flag to send the event.
			 */
			sendAEN = TRUE;
		}
	}

	/*
	 * Generate a system event if flag is set to let anyone who cares know
	 * that an event has occurred.
	 */
	if (sendAEN) {
//SLM-how to send a system event (see kqueue, kevent)
//		(void) ddi_log_sysevent(mpt->m_dip, DDI_VENDOR_LSI, "MPT_SAS",
//		    "SAS", NULL, NULL, DDI_NOSLEEP);
	}
}