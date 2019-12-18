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
typedef  int uint32_t ;
struct dtsec_regs {int /*<<< orphan*/  imask; int /*<<< orphan*/  ecntrl; int /*<<< orphan*/  cam2; int /*<<< orphan*/  cam1; } ;
typedef  enum dtsec_stat_level { ____Placeholder_dtsec_stat_level } dtsec_stat_level ;

/* Variables and functions */
 int CAM1_ERRORS_ONLY ; 
 int /*<<< orphan*/  CAM1_MIB_GRP_1 ; 
 int CAM2_ERRORS_ONLY ; 
 int /*<<< orphan*/  CAM2_MIB_GRP_1 ; 
 int DTSEC_ECNTRL_STEN ; 
 int DTSEC_IMASK_MSROEN ; 
 int EINVAL ; 
#define  E_MAC_STAT_FULL 131 
#define  E_MAC_STAT_MIB_GRP1 130 
#define  E_MAC_STAT_NONE 129 
#define  E_MAC_STAT_PARTIAL 128 
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

int fman_dtsec_set_stat_level(struct dtsec_regs *regs, enum dtsec_stat_level level)
{
	switch (level) {
	case E_MAC_STAT_NONE:
		iowrite32be(0xffffffff, &regs->cam1);
		iowrite32be(0xffffffff, &regs->cam2);
		iowrite32be(ioread32be(&regs->ecntrl) & ~DTSEC_ECNTRL_STEN,
				&regs->ecntrl);
		iowrite32be(ioread32be(&regs->imask) & ~DTSEC_IMASK_MSROEN,
				&regs->imask);
		break;
	case E_MAC_STAT_PARTIAL:
		iowrite32be(CAM1_ERRORS_ONLY, &regs->cam1);
		iowrite32be(CAM2_ERRORS_ONLY, &regs->cam2);
		iowrite32be(ioread32be(&regs->ecntrl) | DTSEC_ECNTRL_STEN,
				&regs->ecntrl);
		iowrite32be(ioread32be(&regs->imask) | DTSEC_IMASK_MSROEN,
				&regs->imask);
		break;
	case E_MAC_STAT_MIB_GRP1:
		iowrite32be((uint32_t)~CAM1_MIB_GRP_1, &regs->cam1);
		iowrite32be((uint32_t)~CAM2_MIB_GRP_1, &regs->cam2);
		iowrite32be(ioread32be(&regs->ecntrl) | DTSEC_ECNTRL_STEN,
				&regs->ecntrl);
		iowrite32be(ioread32be(&regs->imask) | DTSEC_IMASK_MSROEN,
				&regs->imask);
		break;
	case E_MAC_STAT_FULL:
		iowrite32be(0, &regs->cam1);
		iowrite32be(0, &regs->cam2);
		iowrite32be(ioread32be(&regs->ecntrl) | DTSEC_ECNTRL_STEN,
				&regs->ecntrl);
		iowrite32be(ioread32be(&regs->imask) | DTSEC_IMASK_MSROEN,
				&regs->imask);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}