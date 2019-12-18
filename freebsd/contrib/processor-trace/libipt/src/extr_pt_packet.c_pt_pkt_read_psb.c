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
struct pt_config {int /*<<< orphan*/  const* end; } ;

/* Variables and functions */
 int /*<<< orphan*/  pt_opcs_psb ; 
 scalar_t__ pt_psb_hi ; 
 scalar_t__ pt_psb_lo ; 
 int pt_psb_repeat_count ; 
 int pte_bad_packet ; 
 int pte_eos ; 
 int pte_internal ; 
 int ptps_psb ; 

int pt_pkt_read_psb(const uint8_t *pos, const struct pt_config *config)
{
	int count;

	if (!pos || !config)
		return -pte_internal;

	if (config->end < pos + ptps_psb)
		return -pte_eos;

	pos += pt_opcs_psb;

	for (count = 0; count < pt_psb_repeat_count; ++count) {
		if (*pos++ != pt_psb_hi)
			return -pte_bad_packet;
		if (*pos++ != pt_psb_lo)
			return -pte_bad_packet;
	}

	return ptps_psb;
}