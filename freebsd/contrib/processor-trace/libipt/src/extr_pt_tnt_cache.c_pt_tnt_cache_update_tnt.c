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
typedef  int uint8_t ;
struct pt_tnt_cache {int index; int /*<<< orphan*/  tnt; } ;
struct pt_packet_tnt {int bit_size; int /*<<< orphan*/  payload; } ;
struct pt_config {int dummy; } ;

/* Variables and functions */
 int pte_bad_context ; 
 int pte_bad_packet ; 
 int pte_invalid ; 

int pt_tnt_cache_update_tnt(struct pt_tnt_cache *cache,
			    const struct pt_packet_tnt *packet,
			    const struct pt_config *config)
{
	uint8_t bit_size;

	(void) config;

	if (!cache || !packet)
		return -pte_invalid;

	if (cache->index)
		return -pte_bad_context;

	bit_size = packet->bit_size;
	if (!bit_size)
		return -pte_bad_packet;

	cache->tnt = packet->payload;
	cache->index = 1ull << (bit_size - 1);

	return 0;
}