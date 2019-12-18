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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  void* uint32_t ;
struct pt_packet_mwait {void* ext; void* hints; } ;
struct pt_config {int /*<<< orphan*/  const* end; } ;

/* Variables and functions */
 int pt_opcs_mwait ; 
 scalar_t__ pt_pkt_read_value (int /*<<< orphan*/  const*,int) ; 
 int pt_pl_mwait_ext_size ; 
 int pt_pl_mwait_hints_size ; 
 int pte_eos ; 
 int pte_internal ; 
 int ptps_mwait ; 

int pt_pkt_read_mwait(struct pt_packet_mwait *packet, const uint8_t *pos,
		      const struct pt_config *config)
{
	if (!packet || !pos || !config)
		return -pte_internal;

	if (config->end < pos + ptps_mwait)
		return -pte_eos;

	packet->hints = (uint32_t) pt_pkt_read_value(pos + pt_opcs_mwait,
						     pt_pl_mwait_hints_size);
	packet->ext = (uint32_t) pt_pkt_read_value(pos + pt_opcs_mwait +
						   pt_pl_mwait_hints_size,
						   pt_pl_mwait_ext_size);
	return ptps_mwait;
}