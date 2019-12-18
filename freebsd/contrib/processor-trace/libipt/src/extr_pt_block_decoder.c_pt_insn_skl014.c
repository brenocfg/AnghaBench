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
struct TYPE_3__ {int is_direct; } ;
struct TYPE_4__ {TYPE_1__ branch; } ;
struct pt_insn_ext {TYPE_2__ variant; } ;
struct pt_insn {int iclass; } ;

/* Variables and functions */
 int pt_insn_changes_cr3 (struct pt_insn const*,struct pt_insn_ext const*) ; 
#define  ptic_call 130 
#define  ptic_jump 129 
#define  ptic_other 128 

__attribute__((used)) static int pt_insn_skl014(const struct pt_insn *insn,
			  const struct pt_insn_ext *iext)
{
	if (!insn || !iext)
		return 0;

	switch (insn->iclass) {
	default:
		return 0;

	case ptic_call:
	case ptic_jump:
		return iext->variant.branch.is_direct;

	case ptic_other:
		return pt_insn_changes_cr3(insn, iext);
	}
}