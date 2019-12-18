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
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/ * begin; } ;
struct pt_packet_decoder {int /*<<< orphan*/ * sync; TYPE_1__ config; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int pte_invalid ; 
 int pte_nosync ; 

int pt_pkt_get_sync_offset(const struct pt_packet_decoder *decoder,
			   uint64_t *offset)
{
	const uint8_t *begin, *sync;

	if (!decoder || !offset)
		return -pte_invalid;

	begin = decoder->config.begin;
	sync = decoder->sync;

	if (!sync)
		return -pte_nosync;

	*offset = (uint64_t) (int64_t) (sync - begin);
	return 0;
}