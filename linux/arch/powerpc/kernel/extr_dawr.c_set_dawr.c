#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct arch_hw_breakpoint {unsigned long address; int type; int len; } ;
struct TYPE_2__ {int (* set_dawr ) (unsigned long,unsigned long) ;} ;

/* Variables and functions */
 int HW_BRK_TYPE_PRIV_ALL ; 
 int HW_BRK_TYPE_READ ; 
 int HW_BRK_TYPE_TRANSLATE ; 
 int HW_BRK_TYPE_WRITE ; 
 int /*<<< orphan*/  SPRN_DAWR ; 
 int /*<<< orphan*/  SPRN_DAWRX ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,unsigned long) ; 
 TYPE_1__ ppc_md ; 
 int stub1 (unsigned long,unsigned long) ; 

int set_dawr(struct arch_hw_breakpoint *brk)
{
	unsigned long dawr, dawrx, mrd;

	dawr = brk->address;

	dawrx  = (brk->type & (HW_BRK_TYPE_READ | HW_BRK_TYPE_WRITE))
		<< (63 - 58);
	dawrx |= ((brk->type & (HW_BRK_TYPE_TRANSLATE)) >> 2) << (63 - 59);
	dawrx |= (brk->type & (HW_BRK_TYPE_PRIV_ALL)) >> 3;
	/*
	 * DAWR length is stored in field MDR bits 48:53.  Matches range in
	 * doublewords (64 bits) baised by -1 eg. 0b000000=1DW and
	 * 0b111111=64DW.
	 * brk->len is in bytes.
	 * This aligns up to double word size, shifts and does the bias.
	 */
	mrd = ((brk->len + 7) >> 3) - 1;
	dawrx |= (mrd & 0x3f) << (63 - 53);

	if (ppc_md.set_dawr)
		return ppc_md.set_dawr(dawr, dawrx);

	mtspr(SPRN_DAWR, dawr);
	mtspr(SPRN_DAWRX, dawrx);

	return 0;
}