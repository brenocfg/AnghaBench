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

/* Variables and functions */
 scalar_t__ DADDI_WAR ; 
 int /*<<< orphan*/  T9 ; 
 int /*<<< orphan*/  UASM_i_ADDIU (int /*<<< orphan*/ **,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  UASM_i_ADDU (int /*<<< orphan*/ **,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZERO ; 
 scalar_t__ cpu_has_64bit_gp_regs ; 
 scalar_t__ r4k_daddiu_bug () ; 
 int /*<<< orphan*/  uasm_i_addiu (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  uasm_i_daddu (int /*<<< orphan*/ **,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uasm_i_lui (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uasm_rel_hi (unsigned int) ; 
 unsigned int uasm_rel_lo (unsigned int) ; 

__attribute__((used)) static inline void
pg_addiu(u32 **buf, unsigned int reg1, unsigned int reg2, unsigned int off)
{
	if (cpu_has_64bit_gp_regs && DADDI_WAR && r4k_daddiu_bug()) {
		if (off > 0x7fff) {
			uasm_i_lui(buf, T9, uasm_rel_hi(off));
			uasm_i_addiu(buf, T9, T9, uasm_rel_lo(off));
		} else
			uasm_i_addiu(buf, T9, ZERO, off);
		uasm_i_daddu(buf, reg1, reg2, T9);
	} else {
		if (off > 0x7fff) {
			uasm_i_lui(buf, T9, uasm_rel_hi(off));
			uasm_i_addiu(buf, T9, T9, uasm_rel_lo(off));
			UASM_i_ADDU(buf, reg1, reg2, T9);
		} else
			UASM_i_ADDIU(buf, reg1, reg2, off);
	}
}