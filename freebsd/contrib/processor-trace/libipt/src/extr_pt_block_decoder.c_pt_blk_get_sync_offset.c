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
typedef  int /*<<< orphan*/  uint64_t ;
struct pt_block_decoder {int /*<<< orphan*/  query; } ;

/* Variables and functions */
 int pt_qry_get_sync_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pte_invalid ; 

int pt_blk_get_sync_offset(const struct pt_block_decoder *decoder,
			   uint64_t *offset)
{
	if (!decoder)
		return -pte_invalid;

	return pt_qry_get_sync_offset(&decoder->query, offset);
}