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
typedef  scalar_t__ uint8_t ;
struct pt_config {scalar_t__* begin; scalar_t__* end; } ;

/* Variables and functions */
 scalar_t__ const pt_ext_psb ; 
 scalar_t__ const pt_opc_psb ; 
 int pt_pkt_read_psb (scalar_t__ const*,struct pt_config const*) ; 
 scalar_t__ const pt_psb_hi ; 
 scalar_t__ pt_psb_lo ; 
 int /*<<< orphan*/  ptps_psb ; 

__attribute__((used)) static const uint8_t *pt_find_psb(const uint8_t *pos,
				  const struct pt_config *config)
{
	const uint8_t *begin, *end;
	int errcode;

	if (!pos || !config)
		return NULL;

	begin = config->begin;
	end = config->end;

	/* Navigate to the end of the psb payload pattern.
	 *
	 * Beware that PSB is an extended opcode. We must not confuse the extend
	 * opcode of the following packet as belonging to the PSB.
	 */
	if (*pos != pt_psb_hi)
		pos++;

	for (; (pos + 1) < end; pos += 2) {
		uint8_t hi, lo;

		hi = pos[0];
		lo = pos[1];

		if (hi != pt_psb_hi)
			break;

		if (lo != pt_psb_lo)
			break;
	}
	/*
	 * We're right after the psb payload and within the buffer.
	 * Navigate to the expected beginning of the psb packet.
	 */
	pos -= ptps_psb;

	/* Check if we're still inside the buffer. */
	if (pos < begin)
		return NULL;

	/* Check that this is indeed a psb packet we're at. */
	if (pos[0] != pt_opc_psb || pos[1] != pt_ext_psb)
		return NULL;

	errcode = pt_pkt_read_psb(pos, config);
	if (errcode < 0)
		return NULL;

	return pos;
}