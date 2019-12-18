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
struct ndis_events_data {int /*<<< orphan*/  pLoc; int /*<<< orphan*/  pSvc; int /*<<< orphan*/  event_avail; int /*<<< orphan*/  write_pipe; int /*<<< orphan*/  read_pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CoUninitialize () ; 
 int /*<<< orphan*/  IWbemLocator_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWbemServices_Release (int /*<<< orphan*/ ) ; 
 scalar_t__ wmi_refcnt ; 

__attribute__((used)) static void ndis_events_destructor(struct ndis_events_data *events)
{
	CloseHandle(events->read_pipe);
	CloseHandle(events->write_pipe);
	CloseHandle(events->event_avail);
	IWbemServices_Release(events->pSvc);
	IWbemLocator_Release(events->pLoc);
	if (--wmi_refcnt == 0)
		CoUninitialize();
}