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
struct pt_block_decoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pt_blk_reset (struct pt_block_decoder*) ; 
 int pte_internal ; 

__attribute__((used)) static int pt_blk_sync_reset(struct pt_block_decoder *decoder)
{
	if (!decoder)
		return -pte_internal;

	pt_blk_reset(decoder);

	return 0;
}