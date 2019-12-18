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
#define  PTI_INST_MOV_CR3 128 

int pt_insn_changes_cr3(const struct pt_insn *insn,
			const struct pt_insn_ext *iext)
{
	(void) insn;

	if (!iext)
		return 0;

	switch (iext->iclass) {
	default:
		return 0;

	case PTI_INST_MOV_CR3:
		return 1;
	}
}