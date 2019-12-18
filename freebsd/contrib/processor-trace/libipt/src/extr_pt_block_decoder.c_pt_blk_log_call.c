#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  displacement; scalar_t__ is_direct; } ;
struct TYPE_4__ {TYPE_1__ branch; } ;
struct pt_insn_ext {TYPE_2__ variant; } ;
struct pt_insn {scalar_t__ iclass; scalar_t__ size; scalar_t__ ip; } ;
struct pt_block_decoder {int /*<<< orphan*/  retstack; } ;

/* Variables and functions */
 int pt_retstack_push (int /*<<< orphan*/ *,scalar_t__) ; 
 int pte_internal ; 
 scalar_t__ ptic_call ; 

__attribute__((used)) static inline int pt_blk_log_call(struct pt_block_decoder *decoder,
				  const struct pt_insn *insn,
				  const struct pt_insn_ext *iext)
{
	if (!decoder || !insn || !iext)
		return -pte_internal;

	if (insn->iclass != ptic_call)
		return 0;

	/* Ignore direct calls to the next instruction that are used for
	 * position independent code.
	 */
	if (iext->variant.branch.is_direct &&
	    !iext->variant.branch.displacement)
		return 0;

	return pt_retstack_push(&decoder->retstack, insn->ip + insn->size);
}