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
struct pt_block_decoder {int /*<<< orphan*/  asid; } ;
struct pt_asid {int dummy; } ;

/* Variables and functions */
 int pt_asid_to_user (struct pt_asid*,int /*<<< orphan*/ *,size_t) ; 
 int pte_invalid ; 

int pt_blk_asid(const struct pt_block_decoder *decoder, struct pt_asid *asid,
		size_t size)
{
	if (!decoder || !asid)
		return -pte_invalid;

	return pt_asid_to_user(asid, &decoder->asid, size);
}