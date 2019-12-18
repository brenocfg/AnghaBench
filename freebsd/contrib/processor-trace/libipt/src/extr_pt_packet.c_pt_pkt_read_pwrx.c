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
struct pt_packet_pwrx {int interrupt; int store; int autonomous; void* deepest; void* last; } ;
struct pt_config {void* const* end; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct pt_packet_pwrx*,int /*<<< orphan*/ ,int) ; 
 int pt_opcs_pwrx ; 
 int pt_pkt_read_value (void* const*,int /*<<< orphan*/ ) ; 
 int pt_pl_pwrx_deepest_mask ; 
 int pt_pl_pwrx_deepest_shr ; 
 int pt_pl_pwrx_last_mask ; 
 int pt_pl_pwrx_last_shr ; 
 int /*<<< orphan*/  pt_pl_pwrx_size ; 
 int pt_pl_pwrx_wr_hw ; 
 int pt_pl_pwrx_wr_int ; 
 int pt_pl_pwrx_wr_store ; 
 int pte_eos ; 
 int pte_internal ; 
 int ptps_pwrx ; 

int pt_pkt_read_pwrx(struct pt_packet_pwrx *packet, const uint8_t *pos,
		     const struct pt_config *config)
{
	uint64_t payload;

	if (!packet || !pos || !config)
		return -pte_internal;

	if (config->end < pos + ptps_pwrx)
		return -pte_eos;

	payload = pt_pkt_read_value(pos + pt_opcs_pwrx, pt_pl_pwrx_size);

	memset(packet, 0, sizeof(*packet));
	packet->last = (uint8_t) ((payload & pt_pl_pwrx_last_mask) >>
				  pt_pl_pwrx_last_shr);
	packet->deepest = (uint8_t) ((payload & pt_pl_pwrx_deepest_mask) >>
				     pt_pl_pwrx_deepest_shr);
	if (payload & pt_pl_pwrx_wr_int)
		packet->interrupt = 1;
	if (payload & pt_pl_pwrx_wr_store)
		packet->store = 1;
	if (payload & pt_pl_pwrx_wr_hw)
		packet->autonomous = 1;

	return ptps_pwrx;
}