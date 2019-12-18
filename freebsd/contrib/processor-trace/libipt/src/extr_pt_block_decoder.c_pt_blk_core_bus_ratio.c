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
typedef  int /*<<< orphan*/  uint32_t ;
struct pt_block_decoder {int /*<<< orphan*/  query; } ;

/* Variables and functions */
 int pt_qry_core_bus_ratio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pte_invalid ; 

int pt_blk_core_bus_ratio(struct pt_block_decoder *decoder, uint32_t *cbr)
{
	if (!decoder || !cbr)
		return -pte_invalid;

	return pt_qry_core_bus_ratio(&decoder->query, cbr);
}