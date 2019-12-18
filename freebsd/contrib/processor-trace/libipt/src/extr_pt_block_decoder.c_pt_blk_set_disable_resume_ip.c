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
struct pt_insn {int iclass; unsigned long long ip; unsigned long long size; } ;
struct pt_block_decoder {unsigned long long ip; } ;

/* Variables and functions */
 int pte_internal ; 
#define  ptic_call 129 
#define  ptic_far_call 128 

__attribute__((used)) static int pt_blk_set_disable_resume_ip(struct pt_block_decoder *decoder,
					const struct pt_insn *insn)
{
	if (!decoder || !insn)
		return -pte_internal;

	switch (insn->iclass) {
	case ptic_call:
	case ptic_far_call:
		decoder->ip = insn->ip + insn->size;
		break;

	default:
		decoder->ip = 0ull;
		break;
	}

	return 0;
}