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
typedef  void* uint8_t ;
typedef  int uint64_t ;
struct pt_packet_pwre {int hw; void* sub_state; void* state; } ;
struct pt_config {void* const* end; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct pt_packet_pwre*,int /*<<< orphan*/ ,int) ; 
 int pt_opcs_pwre ; 
 int pt_pkt_read_value (void* const*,int /*<<< orphan*/ ) ; 
 int pt_pl_pwre_hw_mask ; 
 int /*<<< orphan*/  pt_pl_pwre_size ; 
 int pt_pl_pwre_state_mask ; 
 int pt_pl_pwre_state_shr ; 
 int pt_pl_pwre_sub_state_mask ; 
 int pt_pl_pwre_sub_state_shr ; 
 int pte_eos ; 
 int pte_internal ; 
 int ptps_pwre ; 

int pt_pkt_read_pwre(struct pt_packet_pwre *packet, const uint8_t *pos,
		     const struct pt_config *config)
{
	uint64_t payload;

	if (!packet || !pos || !config)
		return -pte_internal;

	if (config->end < pos + ptps_pwre)
		return -pte_eos;

	payload = pt_pkt_read_value(pos + pt_opcs_pwre, pt_pl_pwre_size);

	memset(packet, 0, sizeof(*packet));
	packet->state = (uint8_t) ((payload & pt_pl_pwre_state_mask) >>
				   pt_pl_pwre_state_shr);
	packet->sub_state = (uint8_t) ((payload & pt_pl_pwre_sub_state_mask) >>
				       pt_pl_pwre_sub_state_shr);
	if (payload & pt_pl_pwre_hw_mask)
		packet->hw = 1;

	return ptps_pwre;
}