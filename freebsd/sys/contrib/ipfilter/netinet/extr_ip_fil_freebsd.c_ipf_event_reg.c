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
 int /*<<< orphan*/  EVENTHANDLER_PRI_ANY ; 
 void* EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* V_ipf_arrivetag ; 
 void* V_ipf_clonetag ; 
 void* V_ipf_departtag ; 
 int /*<<< orphan*/  if_clone_event ; 
 int /*<<< orphan*/  ifnet_arrival_event ; 
 int /*<<< orphan*/  ifnet_departure_event ; 
 int /*<<< orphan*/  ipf_ifevent ; 

void
ipf_event_reg(void)
{
	V_ipf_arrivetag = EVENTHANDLER_REGISTER(ifnet_arrival_event, \
					       ipf_ifevent, NULL, \
					       EVENTHANDLER_PRI_ANY);
	V_ipf_departtag = EVENTHANDLER_REGISTER(ifnet_departure_event, \
					       ipf_ifevent, NULL, \
					       EVENTHANDLER_PRI_ANY);
#if 0
	V_ipf_clonetag  = EVENTHANDLER_REGISTER(if_clone_event, ipf_ifevent, \
					       NULL, EVENTHANDLER_PRI_ANY);
#endif
}