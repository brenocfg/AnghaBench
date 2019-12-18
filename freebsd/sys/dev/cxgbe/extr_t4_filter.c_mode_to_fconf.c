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
typedef  int uint32_t ;

/* Variables and functions */
 int F_ETHERTYPE ; 
 int F_FCOE ; 
 int F_FRAGMENTATION ; 
 int F_MACMATCH ; 
 int F_MPSHITTYPE ; 
 int F_PORT ; 
 int F_PROTOCOL ; 
 int F_TOS ; 
 int F_VLAN ; 
 int F_VNIC_ID ; 
 int T4_FILTER_ETH_TYPE ; 
 int T4_FILTER_FCoE ; 
 int T4_FILTER_IP_FRAGMENT ; 
 int T4_FILTER_IP_PROTO ; 
 int T4_FILTER_IP_TOS ; 
 int T4_FILTER_MAC_IDX ; 
 int T4_FILTER_MPS_HIT_TYPE ; 
 int T4_FILTER_PORT ; 
 int T4_FILTER_VLAN ; 
 int T4_FILTER_VNIC ; 

__attribute__((used)) static uint32_t
mode_to_fconf(uint32_t mode)
{
	uint32_t fconf = 0;

	if (mode & T4_FILTER_IP_FRAGMENT)
		fconf |= F_FRAGMENTATION;

	if (mode & T4_FILTER_MPS_HIT_TYPE)
		fconf |= F_MPSHITTYPE;

	if (mode & T4_FILTER_MAC_IDX)
		fconf |= F_MACMATCH;

	if (mode & T4_FILTER_ETH_TYPE)
		fconf |= F_ETHERTYPE;

	if (mode & T4_FILTER_IP_PROTO)
		fconf |= F_PROTOCOL;

	if (mode & T4_FILTER_IP_TOS)
		fconf |= F_TOS;

	if (mode & T4_FILTER_VLAN)
		fconf |= F_VLAN;

	if (mode & T4_FILTER_VNIC)
		fconf |= F_VNIC_ID;

	if (mode & T4_FILTER_PORT)
		fconf |= F_PORT;

	if (mode & T4_FILTER_FCoE)
		fconf |= F_FCOE;

	return (fconf);
}