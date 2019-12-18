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
struct pt_block_decoder {unsigned long long ip; int /*<<< orphan*/  asid; int /*<<< orphan*/  retstack; int /*<<< orphan*/  event; scalar_t__ bound_ptwrite; scalar_t__ bound_vmcs; scalar_t__ bound_paging; scalar_t__ process_insn; scalar_t__ speculative; scalar_t__ process_event; scalar_t__ enabled; scalar_t__ status; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pt_asid_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pt_retstack_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptem_unknown ; 

__attribute__((used)) static void pt_blk_reset(struct pt_block_decoder *decoder)
{
	if (!decoder)
		return;

	decoder->mode = ptem_unknown;
	decoder->ip = 0ull;
	decoder->status = 0;
	decoder->enabled = 0;
	decoder->process_event = 0;
	decoder->speculative = 0;
	decoder->process_insn = 0;
	decoder->bound_paging = 0;
	decoder->bound_vmcs = 0;
	decoder->bound_ptwrite = 0;

	memset(&decoder->event, 0, sizeof(decoder->event));
	pt_retstack_init(&decoder->retstack);
	pt_asid_init(&decoder->asid);
}