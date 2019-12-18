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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/ * end; int /*<<< orphan*/ * begin; } ;
struct pt_packet_decoder {int /*<<< orphan*/  const* pos; int /*<<< orphan*/  const* sync; TYPE_1__ config; } ;

/* Variables and functions */
 int pte_eos ; 
 int pte_invalid ; 

int pt_pkt_sync_set(struct pt_packet_decoder *decoder, uint64_t offset)
{
	const uint8_t *begin, *end, *pos;

	if (!decoder)
		return -pte_invalid;

	begin = decoder->config.begin;
	end = decoder->config.end;
	pos = begin + offset;

	if (end < pos || pos < begin)
		return -pte_eos;

	decoder->sync = pos;
	decoder->pos = pos;

	return 0;
}