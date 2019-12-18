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
struct pt_packet_mtc {int /*<<< orphan*/  ctc; } ;
struct pt_config {int /*<<< orphan*/  const* end; } ;

/* Variables and functions */
 size_t pt_opcs_mtc ; 
 int pte_eos ; 
 int pte_internal ; 
 int ptps_mtc ; 

int pt_pkt_read_mtc(struct pt_packet_mtc *packet, const uint8_t *pos,
		    const struct pt_config *config)
{
	if (!packet || !pos || !config)
		return -pte_internal;

	if (config->end < pos + ptps_mtc)
		return -pte_eos;

	packet->ctc = pos[pt_opcs_mtc];

	return ptps_mtc;
}