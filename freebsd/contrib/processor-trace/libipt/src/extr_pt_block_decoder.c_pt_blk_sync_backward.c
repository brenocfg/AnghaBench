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
struct pt_block_decoder {int /*<<< orphan*/  ip; int /*<<< orphan*/  query; } ;

/* Variables and functions */
 int pt_blk_start (struct pt_block_decoder*,int) ; 
 int pt_blk_sync_reset (struct pt_block_decoder*) ; 
 int pt_qry_sync_backward (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pte_invalid ; 

int pt_blk_sync_backward(struct pt_block_decoder *decoder)
{
	int errcode, status;

	if (!decoder)
		return -pte_invalid;

	errcode = pt_blk_sync_reset(decoder);
	if (errcode < 0)
		return errcode;

	status = pt_qry_sync_backward(&decoder->query, &decoder->ip);

	return pt_blk_start(decoder, status);
}