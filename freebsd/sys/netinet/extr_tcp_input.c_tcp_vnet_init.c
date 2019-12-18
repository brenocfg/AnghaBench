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
 int /*<<< orphan*/  COUNTER_ARRAY_ALLOC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  TCP_NSTATES ; 
 int /*<<< orphan*/  VNET_PCPUSTAT_ALLOC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_tcps_states ; 
 int /*<<< orphan*/  tcpstat ; 

__attribute__((used)) static void
tcp_vnet_init(const void *unused)
{

	COUNTER_ARRAY_ALLOC(V_tcps_states, TCP_NSTATES, M_WAITOK);
	VNET_PCPUSTAT_ALLOC(tcpstat, M_WAITOK);
}