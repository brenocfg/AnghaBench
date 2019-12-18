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
struct pt_packet_tsc {int /*<<< orphan*/  tsc; } ;
struct pt_config {int /*<<< orphan*/  const* end; } ;

/* Variables and functions */
 int pt_opcs_tsc ; 
 int /*<<< orphan*/  pt_pkt_read_value (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_pl_tsc_size ; 
 int pte_eos ; 
 int pte_internal ; 
 int ptps_tsc ; 

int pt_pkt_read_tsc(struct pt_packet_tsc *packet, const uint8_t *pos,
		    const struct pt_config *config)
{
	if (!packet || !pos || !config)
		return -pte_internal;

	if (config->end < pos + ptps_tsc)
		return -pte_eos;

	packet->tsc = pt_pkt_read_value(pos + pt_opcs_tsc, pt_pl_tsc_size);

	return ptps_tsc;
}