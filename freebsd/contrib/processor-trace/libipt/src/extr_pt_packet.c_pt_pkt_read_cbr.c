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
struct pt_packet_cbr {int /*<<< orphan*/  ratio; } ;
struct pt_config {int /*<<< orphan*/  const* end; } ;

/* Variables and functions */
 int pte_eos ; 
 int pte_internal ; 
 int ptps_cbr ; 

int pt_pkt_read_cbr(struct pt_packet_cbr *packet, const uint8_t *pos,
		    const struct pt_config *config)
{
	if (!packet || !pos || !config)
		return -pte_internal;

	if (config->end < pos + ptps_cbr)
		return -pte_eos;

	packet->ratio = pos[2];

	return ptps_cbr;
}