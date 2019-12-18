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
struct vmbus_softc {int dummy; } ;
struct vmbus_evtflags {int /*<<< orphan*/  evt_flags; } ;

/* Variables and functions */
 struct vmbus_evtflags* VMBUS_PCPU_GET (struct vmbus_softc*,int /*<<< orphan*/ ,int) ; 
 int VMBUS_SINT_MESSAGE ; 
 int /*<<< orphan*/  event_flags ; 
 int /*<<< orphan*/  event_flags_cnt ; 
 int /*<<< orphan*/  vmbus_event_flags_proc (struct vmbus_softc*,int /*<<< orphan*/ ,struct vmbus_evtflags*) ; 

void
vmbus_event_proc(struct vmbus_softc *sc, int cpu)
{
	struct vmbus_evtflags *eventf;

	/*
	 * On Host with Win8 or above, the event page can be checked directly
	 * to get the id of the channel that has the pending interrupt.
	 */
	eventf = VMBUS_PCPU_GET(sc, event_flags, cpu) + VMBUS_SINT_MESSAGE;
	vmbus_event_flags_proc(sc, eventf->evt_flags,
	    VMBUS_PCPU_GET(sc, event_flags_cnt, cpu));
}