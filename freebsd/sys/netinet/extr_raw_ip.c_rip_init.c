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
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INP_PCBHASH_RAW_SIZE ; 
 int /*<<< orphan*/  IPI_HASHFIELDS_NONE ; 
 int /*<<< orphan*/  V_ripcb ; 
 int /*<<< orphan*/  V_ripcbinfo ; 
 int /*<<< orphan*/  in_pcbinfo_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maxsockets_change ; 
 int /*<<< orphan*/  rip_inpcb_init ; 
 int /*<<< orphan*/  rip_zone_change ; 

void
rip_init(void)
{

	in_pcbinfo_init(&V_ripcbinfo, "rip", &V_ripcb, INP_PCBHASH_RAW_SIZE,
	    1, "ripcb", rip_inpcb_init, IPI_HASHFIELDS_NONE);
	EVENTHANDLER_REGISTER(maxsockets_change, rip_zone_change, NULL,
	    EVENTHANDLER_PRI_ANY);
}