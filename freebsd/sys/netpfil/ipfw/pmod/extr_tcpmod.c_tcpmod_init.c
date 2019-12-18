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
 int ENXIO ; 
 scalar_t__ V_tcpmod_setmss_eid ; 
 scalar_t__ ipfw_add_eaction (struct ip_fw_chain*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ipfw_tcpmod ; 

int
tcpmod_init(struct ip_fw_chain *ch, int first)
{

	V_tcpmod_setmss_eid = ipfw_add_eaction(ch, ipfw_tcpmod, "tcp-setmss");
	if (V_tcpmod_setmss_eid == 0)
		return (ENXIO);
	return (0);
}