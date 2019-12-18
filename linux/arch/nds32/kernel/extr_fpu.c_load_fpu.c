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
struct fpu_struct {int dummy; } ;

/* Variables and functions */
 unsigned int FPCFG_mskFREG ; 
 unsigned int FPCFG_offFREG ; 
#define  SP16_DP8_reg 131 
#define  SP32_DP16_reg 130 
#define  SP32_DP32_reg 129 
#define  SP8_DP4_reg 128 
 unsigned int __nds32__fmfcfg () ; 
 int /*<<< orphan*/  disable_fpu () ; 
 int /*<<< orphan*/  enable_fpu () ; 

void load_fpu(const struct fpu_struct *fpregs)
{
	unsigned int fpcfg, fpcsr;

	enable_fpu();
	fpcfg = ((__nds32__fmfcfg() & FPCFG_mskFREG) >> FPCFG_offFREG);
	switch (fpcfg) {
	case SP32_DP32_reg:
		asm volatile ("fldi $fd31, [%0+0xf8]\n\t"
			      "fldi $fd30, [%0+0xf0]\n\t"
			      "fldi $fd29, [%0+0xe8]\n\t"
			      "fldi $fd28, [%0+0xe0]\n\t"
			      "fldi $fd27, [%0+0xd8]\n\t"
			      "fldi $fd26, [%0+0xd0]\n\t"
			      "fldi $fd25, [%0+0xc8]\n\t"
			      "fldi $fd24, [%0+0xc0]\n\t"
			      "fldi $fd23, [%0+0xb8]\n\t"
			      "fldi $fd22, [%0+0xb0]\n\t"
			      "fldi $fd21, [%0+0xa8]\n\t"
			      "fldi $fd20, [%0+0xa0]\n\t"
			      "fldi $fd19, [%0+0x98]\n\t"
			      "fldi $fd18, [%0+0x90]\n\t"
			      "fldi $fd17, [%0+0x88]\n\t"
			      "fldi $fd16, [%0+0x80]\n\t"
			      :	/* no output */
			      : "r" (fpregs));
		/* fall through */
	case SP32_DP16_reg:
		asm volatile ("fldi $fd15, [%0+0x78]\n\t"
			      "fldi $fd14, [%0+0x70]\n\t"
			      "fldi $fd13, [%0+0x68]\n\t"
			      "fldi $fd12, [%0+0x60]\n\t"
			      "fldi $fd11, [%0+0x58]\n\t"
			      "fldi $fd10, [%0+0x50]\n\t"
			      "fldi $fd9,  [%0+0x48]\n\t"
			      "fldi $fd8,  [%0+0x40]\n\t"
			      :	/* no output */
			      : "r" (fpregs));
		/* fall through */
	case SP16_DP8_reg:
		asm volatile ("fldi $fd7,  [%0+0x38]\n\t"
			      "fldi $fd6,  [%0+0x30]\n\t"
			      "fldi $fd5,  [%0+0x28]\n\t"
			      "fldi $fd4,  [%0+0x20]\n\t"
			      :	/* no output */
			      : "r" (fpregs));
		/* fall through */
	case SP8_DP4_reg:
		asm volatile ("fldi $fd3,  [%1+0x18]\n\t"
			      "fldi $fd2,  [%1+0x10]\n\t"
			      "fldi $fd1,  [%1+0x8]\n\t"
			      "fldi $fd0,  [%1+0x0]\n\t"
			      "lwi  %0, [%1+0x100]\n\t"
			      "fmtcsr	%0\n\t":"=&r" (fpcsr)
			      : "r"(fpregs));
	}
	disable_fpu();
}