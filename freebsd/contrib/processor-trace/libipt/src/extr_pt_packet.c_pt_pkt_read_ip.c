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
typedef  int uint8_t ;
typedef  unsigned long long uint64_t ;
struct pt_packet_ip {int ipc; unsigned long long ip; } ;
struct pt_config {int const* end; } ;
typedef  enum pt_ip_compression { ____Placeholder_pt_ip_compression } pt_ip_compression ;

/* Variables and functions */
 int pt_opm_ipc_shr ; 
 int pt_opm_ipc_shr_mask ; 
 int pt_pkt_ip_size (int) ; 
 unsigned long long pt_pkt_read_value (int const*,int) ; 
 int pte_eos ; 
 int pte_internal ; 

int pt_pkt_read_ip(struct pt_packet_ip *packet, const uint8_t *pos,
		   const struct pt_config *config)
{
	uint64_t ip;
	uint8_t ipc;
	int ipsize;

	if (!packet || !pos || !config)
		return -pte_internal;

	ipc = (*pos++ >> pt_opm_ipc_shr) & pt_opm_ipc_shr_mask;

	ip = 0ull;
	ipsize = pt_pkt_ip_size((enum pt_ip_compression) ipc);
	if (ipsize < 0)
		return ipsize;

	if (config->end < pos + ipsize)
		return -pte_eos;

	if (ipsize)
		ip = pt_pkt_read_value(pos, ipsize);

	packet->ipc = (enum pt_ip_compression) ipc;
	packet->ip = ip;

	return ipsize + 1;
}