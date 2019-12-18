#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct pt_insn_ext {int dummy; } ;
struct pt_insn {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  ip; } ;
struct TYPE_9__ {TYPE_1__ disabled; } ;
struct pt_event {TYPE_2__ variant; scalar_t__ ip_suppressed; } ;
struct TYPE_13__ {scalar_t__ skl014; } ;
struct TYPE_10__ {scalar_t__ addr_cfg; } ;
struct TYPE_11__ {TYPE_3__ config; } ;
struct TYPE_14__ {TYPE_6__ errata; TYPE_4__ addr_filter; } ;
struct TYPE_12__ {TYPE_7__ config; } ;
struct pt_block_decoder {TYPE_5__ query; } ;
struct pt_block {int dummy; } ;

/* Variables and functions */
 int pt_blk_proceed_skl014 (struct pt_block_decoder*,struct pt_block*,struct pt_insn*,struct pt_insn_ext*) ; 
 int pt_blk_proceed_to_insn (struct pt_block_decoder*,struct pt_block*,struct pt_insn*,struct pt_insn_ext*,int /*<<< orphan*/ ) ; 
 int pt_blk_proceed_to_ip (struct pt_block_decoder*,struct pt_block*,struct pt_insn*,struct pt_insn_ext*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_insn_changes_cr3 ; 
 int pte_internal ; 

__attribute__((used)) static int pt_blk_proceed_to_disabled(struct pt_block_decoder *decoder,
				      struct pt_block *block,
				      struct pt_insn *insn,
				      struct pt_insn_ext *iext,
				      const struct pt_event *ev)
{
	if (!decoder || !block || !ev)
		return -pte_internal;

	if (ev->ip_suppressed) {
		/* Due to SKL014 the TIP.PGD payload may be suppressed also for
		 * direct branches.
		 *
		 * If we don't have a filter configuration we assume that no
		 * address filters were used and the erratum does not apply.
		 *
		 * We might otherwise disable tracing too early.
		 */
		if (decoder->query.config.addr_filter.config.addr_cfg &&
		    decoder->query.config.errata.skl014)
			return pt_blk_proceed_skl014(decoder, block, insn,
						     iext);

		/* A synchronous disabled event also binds to far branches and
		 * CPL-changing instructions.  Both would require trace,
		 * however, and are thus implicitly handled by erroring out.
		 *
		 * The would-require-trace error is handled by our caller.
		 */
		return pt_blk_proceed_to_insn(decoder, block, insn, iext,
					      pt_insn_changes_cr3);
	} else
		return pt_blk_proceed_to_ip(decoder, block, insn, iext,
					    ev->variant.disabled.ip);
}