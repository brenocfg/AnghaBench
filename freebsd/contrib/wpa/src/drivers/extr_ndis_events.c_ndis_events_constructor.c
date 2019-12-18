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
struct ndis_events_data {int ref; int /*<<< orphan*/  write_pipe; int /*<<< orphan*/  read_pipe; int /*<<< orphan*/ * event_avail; } ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreatePipe (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int ndis_events_constructor(struct ndis_events_data *events)
{
	events->ref = 1;

	if (!CreatePipe(&events->read_pipe, &events->write_pipe, NULL, 512)) {
		wpa_printf(MSG_ERROR, "CreatePipe() failed: %d",
			   (int) GetLastError());
		return -1;
	}
	events->event_avail = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (events->event_avail == NULL) {
		wpa_printf(MSG_ERROR, "CreateEvent() failed: %d",
			   (int) GetLastError());
		CloseHandle(events->read_pipe);
		CloseHandle(events->write_pipe);
		return -1;
	}

	return 0;
}