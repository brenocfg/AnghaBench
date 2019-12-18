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
struct pt_packet_ip {int ipc; int ip; } ;
struct pt_last_ip {int suppressed; int ip; int have_ip; } ;
struct pt_config {int dummy; } ;

/* Variables and functions */
#define  pt_ipc_full 133 
#define  pt_ipc_sext_48 132 
#define  pt_ipc_suppressed 131 
#define  pt_ipc_update_16 130 
#define  pt_ipc_update_32 129 
#define  pt_ipc_update_48 128 
 int pte_bad_packet ; 
 int pte_internal ; 
 int sext (int,int) ; 

int pt_last_ip_update_ip(struct pt_last_ip *last_ip,
			 const struct pt_packet_ip *packet,
			 const struct pt_config *config)
{
	(void) config;

	if (!last_ip || !packet)
		return -pte_internal;

	switch (packet->ipc) {
	case pt_ipc_suppressed:
		last_ip->suppressed = 1;
		return 0;

	case pt_ipc_sext_48:
		last_ip->ip = sext(packet->ip, 48);
		last_ip->have_ip = 1;
		last_ip->suppressed = 0;
		return 0;

	case pt_ipc_update_16:
		last_ip->ip = (last_ip->ip & ~0xffffull)
			| (packet->ip & 0xffffull);
		last_ip->have_ip = 1;
		last_ip->suppressed = 0;
		return 0;

	case pt_ipc_update_32:
		last_ip->ip = (last_ip->ip & ~0xffffffffull)
			| (packet->ip & 0xffffffffull);
		last_ip->have_ip = 1;
		last_ip->suppressed = 0;
		return 0;

	case pt_ipc_update_48:
		last_ip->ip = (last_ip->ip & ~0xffffffffffffull)
			| (packet->ip & 0xffffffffffffull);
		last_ip->have_ip = 1;
		last_ip->suppressed = 0;
		return 0;

	case pt_ipc_full:
		last_ip->ip = packet->ip;
		last_ip->have_ip = 1;
		last_ip->suppressed = 0;
		return 0;
	}

	return -pte_bad_packet;
}