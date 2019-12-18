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
struct ip_fw_chain {int dummy; } ;

/* Variables and functions */
 scalar_t__ V_tcpmod_setmss_eid ; 
 int /*<<< orphan*/  ipfw_del_eaction (struct ip_fw_chain*,scalar_t__) ; 

void
tcpmod_uninit(struct ip_fw_chain *ch, int last)
{

	ipfw_del_eaction(ch, V_tcpmod_setmss_eid);
	V_tcpmod_setmss_eid = 0;
}