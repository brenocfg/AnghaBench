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

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * V_ipf_arrivetag ; 
 int /*<<< orphan*/ * V_ipf_clonetag ; 
 int /*<<< orphan*/ * V_ipf_departtag ; 
 int /*<<< orphan*/  if_clone_event ; 
 int /*<<< orphan*/  ifnet_arrival_event ; 
 int /*<<< orphan*/  ifnet_departure_event ; 

void
ipf_event_dereg(void)
{
	if (V_ipf_arrivetag != NULL) {
		EVENTHANDLER_DEREGISTER(ifnet_arrival_event, V_ipf_arrivetag);
	}
	if (V_ipf_departtag != NULL) {
		EVENTHANDLER_DEREGISTER(ifnet_departure_event, V_ipf_departtag);
	}
#if 0
	if (V_ipf_clonetag != NULL) {
		EVENTHANDLER_DEREGISTER(if_clone_event, V_ipf_clonetag);
	}
#endif
}