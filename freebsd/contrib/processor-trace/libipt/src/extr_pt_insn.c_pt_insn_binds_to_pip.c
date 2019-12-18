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
struct pt_insn_ext {int iclass; } ;
struct pt_insn {int dummy; } ;

/* Variables and functions */
#define  PTI_INST_MOV_CR3 130 
#define  PTI_INST_VMLAUNCH 129 
#define  PTI_INST_VMRESUME 128 
 int pt_insn_is_far_branch (struct pt_insn const*,struct pt_insn_ext const*) ; 

int pt_insn_binds_to_pip(const struct pt_insn *insn,
			 const struct pt_insn_ext *iext)
{
	if (!iext)
		return 0;

	switch (iext->iclass) {
	default:
		return pt_insn_is_far_branch(insn, iext);

	case PTI_INST_MOV_CR3:
	case PTI_INST_VMLAUNCH:
	case PTI_INST_VMRESUME:
		return 1;
	}
}