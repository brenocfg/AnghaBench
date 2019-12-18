#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pt_insn_ext {int iclass; } ;
struct pt_insn {int /*<<< orphan*/  ip; int /*<<< orphan*/  mode; } ;
struct TYPE_5__ {int /*<<< orphan*/  ip; int /*<<< orphan*/  at; } ;
struct TYPE_4__ {int /*<<< orphan*/  ip; } ;
struct TYPE_6__ {TYPE_2__ async_disabled; TYPE_1__ disabled; } ;
struct pt_event {TYPE_3__ variant; int /*<<< orphan*/  type; } ;
struct pt_block_decoder {int /*<<< orphan*/  asid; int /*<<< orphan*/  image; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
#define  PTI_INST_VMLAUNCH 129 
#define  PTI_INST_VMRESUME 128 
 int pt_insn_decode (struct pt_insn*,struct pt_insn_ext*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pte_internal ; 
 int /*<<< orphan*/  ptev_disabled ; 

__attribute__((used)) static int pt_blk_handle_erratum_skd022(struct pt_block_decoder *decoder,
					struct pt_event *ev)
{
	struct pt_insn_ext iext;
	struct pt_insn insn;
	int errcode;

	if (!decoder || !ev)
		return -pte_internal;

	insn.mode = decoder->mode;
	insn.ip = ev->variant.async_disabled.at;

	errcode = pt_insn_decode(&insn, &iext, decoder->image, &decoder->asid);
	if (errcode < 0)
		return 0;

	switch (iext.iclass) {
	default:
		/* The erratum does not apply. */
		return 0;

	case PTI_INST_VMLAUNCH:
	case PTI_INST_VMRESUME:
		/* The erratum may apply.  We can't be sure without a lot more
		 * analysis.  Let's assume it does.
		 *
		 * We turn the async disable into a sync disable.  Our caller
		 * will restart event processing.
		 */
		ev->type = ptev_disabled;
		ev->variant.disabled.ip = ev->variant.async_disabled.ip;

		return 1;
	}
}