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
typedef  int /*<<< orphan*/  u32 ;
struct uasm_reloc {scalar_t__ lab; scalar_t__ type; int /*<<< orphan*/ * addr; } ;

/* Variables and functions */
 scalar_t__ R_MIPS_26 ; 
 scalar_t__ R_MIPS_PC16 ; 
 scalar_t__ UASM_LABEL_INVALID ; 

int uasm_insn_has_bdelay(struct uasm_reloc *rel, u32 *addr)
{
	for (; rel->lab != UASM_LABEL_INVALID; rel++) {
		if (rel->addr == addr
		    && (rel->type == R_MIPS_PC16
			|| rel->type == R_MIPS_26))
			return 1;
	}

	return 0;
}