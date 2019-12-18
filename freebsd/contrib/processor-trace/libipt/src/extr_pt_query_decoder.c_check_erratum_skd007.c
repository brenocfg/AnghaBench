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
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;
struct TYPE_2__ {scalar_t__ const* end; } ;
struct pt_query_decoder {scalar_t__* pos; TYPE_1__ config; } ;
struct pt_packet_cyc {scalar_t__ value; } ;

/* Variables and functions */
 scalar_t__ const pt_ext_ovf ; 
 int pte_internal ; 

__attribute__((used)) static int check_erratum_skd007(struct pt_query_decoder *decoder,
				const struct pt_packet_cyc *packet, int size)
{
	const uint8_t *pos;
	uint16_t payload;

	if (!decoder || !packet || size < 0)
		return -pte_internal;

	/* It must be a 2-byte CYC. */
	if (size != 2)
		return 0;

	payload = (uint16_t) packet->value;

	/* The 2nd byte of the CYC payload must look like an ext opcode. */
	if ((payload & ~0x1f) != 0x20)
		return 0;

	/* Skip this CYC packet. */
	pos = decoder->pos + size;
	if (decoder->config.end <= pos)
		return 0;

	/* See if we got a second CYC that looks like an OVF ext opcode. */
	if (*pos != pt_ext_ovf)
		return 0;

	/* We shouldn't get back-to-back CYCs unless they are sent when the
	 * counter wraps around.  In this case, we'd expect a full payload.
	 *
	 * Since we got two non-full CYC packets, we assume the erratum hit.
	 */

	return 1;
}