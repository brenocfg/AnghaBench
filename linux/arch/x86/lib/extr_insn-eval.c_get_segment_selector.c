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
struct pt_regs {int cs; int ss; int ds; int es; int fs; } ;
struct kernel_vm86_regs {short ds; short es; short fs; short gs; } ;

/* Variables and functions */
 short EINVAL ; 
#define  INAT_SEG_REG_CS 134 
#define  INAT_SEG_REG_DS 133 
#define  INAT_SEG_REG_ES 132 
#define  INAT_SEG_REG_FS 131 
#define  INAT_SEG_REG_GS 130 
#define  INAT_SEG_REG_IGNORE 129 
#define  INAT_SEG_REG_SS 128 
 int /*<<< orphan*/  ds ; 
 int /*<<< orphan*/  es ; 
 int /*<<< orphan*/  fs ; 
 short get_user_gs (struct pt_regs*) ; 
 int /*<<< orphan*/  gs ; 
 int /*<<< orphan*/  savesegment (int /*<<< orphan*/ ,unsigned short) ; 
 scalar_t__ v8086_mode (struct pt_regs*) ; 

__attribute__((used)) static short get_segment_selector(struct pt_regs *regs, int seg_reg_idx)
{
#ifdef CONFIG_X86_64
	unsigned short sel;

	switch (seg_reg_idx) {
	case INAT_SEG_REG_IGNORE:
		return 0;
	case INAT_SEG_REG_CS:
		return (unsigned short)(regs->cs & 0xffff);
	case INAT_SEG_REG_SS:
		return (unsigned short)(regs->ss & 0xffff);
	case INAT_SEG_REG_DS:
		savesegment(ds, sel);
		return sel;
	case INAT_SEG_REG_ES:
		savesegment(es, sel);
		return sel;
	case INAT_SEG_REG_FS:
		savesegment(fs, sel);
		return sel;
	case INAT_SEG_REG_GS:
		savesegment(gs, sel);
		return sel;
	default:
		return -EINVAL;
	}
#else /* CONFIG_X86_32 */
	struct kernel_vm86_regs *vm86regs = (struct kernel_vm86_regs *)regs;

	if (v8086_mode(regs)) {
		switch (seg_reg_idx) {
		case INAT_SEG_REG_CS:
			return (unsigned short)(regs->cs & 0xffff);
		case INAT_SEG_REG_SS:
			return (unsigned short)(regs->ss & 0xffff);
		case INAT_SEG_REG_DS:
			return vm86regs->ds;
		case INAT_SEG_REG_ES:
			return vm86regs->es;
		case INAT_SEG_REG_FS:
			return vm86regs->fs;
		case INAT_SEG_REG_GS:
			return vm86regs->gs;
		case INAT_SEG_REG_IGNORE:
			/* fall through */
		default:
			return -EINVAL;
		}
	}

	switch (seg_reg_idx) {
	case INAT_SEG_REG_CS:
		return (unsigned short)(regs->cs & 0xffff);
	case INAT_SEG_REG_SS:
		return (unsigned short)(regs->ss & 0xffff);
	case INAT_SEG_REG_DS:
		return (unsigned short)(regs->ds & 0xffff);
	case INAT_SEG_REG_ES:
		return (unsigned short)(regs->es & 0xffff);
	case INAT_SEG_REG_FS:
		return (unsigned short)(regs->fs & 0xffff);
	case INAT_SEG_REG_GS:
		/*
		 * GS may or may not be in regs as per CONFIG_X86_32_LAZY_GS.
		 * The macro below takes care of both cases.
		 */
		return get_user_gs(regs);
	case INAT_SEG_REG_IGNORE:
		/* fall through */
	default:
		return -EINVAL;
	}
#endif /* CONFIG_X86_64 */
}