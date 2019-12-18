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
typedef  int uint64_t ;
struct pt_packet_vmcs {int base; } ;
struct pt_config {int /*<<< orphan*/  const* end; } ;

/* Variables and functions */
 int pt_opcs_vmcs ; 
 int pt_pkt_read_value (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int pt_pl_vmcs_shl ; 
 int /*<<< orphan*/  pt_pl_vmcs_size ; 
 int pte_eos ; 
 int pte_internal ; 
 int ptps_vmcs ; 

int pt_pkt_read_vmcs(struct pt_packet_vmcs *packet, const uint8_t *pos,
		     const struct pt_config *config)
{
	uint64_t payload;

	if (!packet || !pos || !config)
		return -pte_internal;

	if (config->end < pos + ptps_vmcs)
		return -pte_eos;

	payload = pt_pkt_read_value(pos + pt_opcs_vmcs, pt_pl_vmcs_size);

	packet->base = payload << pt_pl_vmcs_shl;

	return ptps_vmcs;
}