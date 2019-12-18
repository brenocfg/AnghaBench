#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  tsx; int /*<<< orphan*/  exec; } ;
struct pt_packet_mode {int leaf; TYPE_1__ bits; } ;
struct pt_config {int const* end; } ;
typedef  enum pt_mode_leaf { ____Placeholder_pt_mode_leaf } pt_mode_leaf ;

/* Variables and functions */
#define  pt_mol_exec 129 
#define  pt_mol_tsx 128 
 int pt_mom_bits ; 
 int pt_mom_leaf ; 
 size_t pt_opcs_mode ; 
 int pt_pkt_read_mode_exec (int /*<<< orphan*/ *,int) ; 
 int pt_pkt_read_mode_tsx (int /*<<< orphan*/ *,int) ; 
 int pte_bad_packet ; 
 int pte_eos ; 
 int pte_internal ; 
 int ptps_mode ; 

int pt_pkt_read_mode(struct pt_packet_mode *packet, const uint8_t *pos,
		     const struct pt_config *config)
{
	uint8_t payload, mode, leaf;

	if (!packet || !pos || !config)
		return -pte_internal;

	if (config->end < pos + ptps_mode)
		return -pte_eos;

	payload = pos[pt_opcs_mode];
	leaf = payload & pt_mom_leaf;
	mode = payload & pt_mom_bits;

	packet->leaf = (enum pt_mode_leaf) leaf;
	switch (leaf) {
	default:
		return -pte_bad_packet;

	case pt_mol_exec:
		return pt_pkt_read_mode_exec(&packet->bits.exec, mode);

	case pt_mol_tsx:
		return pt_pkt_read_mode_tsx(&packet->bits.tsx, mode);
	}
}