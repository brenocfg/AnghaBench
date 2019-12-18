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
typedef  int u64 ;
typedef  int u32 ;
struct cpuinfo_x86 {int x86; int x86_model; } ;

/* Variables and functions */
 int BIT (int) ; 
 int MSR_AMD64_SMCA_MCx_MISC (unsigned int) ; 
 int /*<<< orphan*/  MSR_K7_HWCR ; 
 int NR_BLOCKS ; 
 scalar_t__ SMCA_IF ; 
 int /*<<< orphan*/  msr_clear_bit (int,int) ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int) ; 
 scalar_t__ smca_get_bank_type (unsigned int) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int) ; 

void disable_err_thresholding(struct cpuinfo_x86 *c, unsigned int bank)
{
	int i, num_msrs;
	u64 hwcr;
	bool need_toggle;
	u32 msrs[NR_BLOCKS];

	if (c->x86 == 0x15 && bank == 4) {
		msrs[0] = 0x00000413; /* MC4_MISC0 */
		msrs[1] = 0xc0000408; /* MC4_MISC1 */
		num_msrs = 2;
	} else if (c->x86 == 0x17 &&
		   (c->x86_model >= 0x10 && c->x86_model <= 0x2F)) {

		if (smca_get_bank_type(bank) != SMCA_IF)
			return;

		msrs[0] = MSR_AMD64_SMCA_MCx_MISC(bank);
		num_msrs = 1;
	} else {
		return;
	}

	rdmsrl(MSR_K7_HWCR, hwcr);

	/* McStatusWrEn has to be set */
	need_toggle = !(hwcr & BIT(18));
	if (need_toggle)
		wrmsrl(MSR_K7_HWCR, hwcr | BIT(18));

	/* Clear CntP bit safely */
	for (i = 0; i < num_msrs; i++)
		msr_clear_bit(msrs[i], 62);

	/* restore old settings */
	if (need_toggle)
		wrmsrl(MSR_K7_HWCR, hwcr);
}