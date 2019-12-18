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

/* Variables and functions */
 int /*<<< orphan*/  APMU_PJ_IDLE_CFG ; 
 int APMU_PJ_IDLE_CFG_ISO_MODE_CNTRL_MASK ; 
 int APMU_PJ_IDLE_CFG_L2_PWR_SW ; 
 int APMU_PJ_IDLE_CFG_PJ_IDLE ; 
 int APMU_PJ_IDLE_CFG_PJ_PWRDWN ; 
 int APMU_PJ_IDLE_CFG_PWR_SW (int) ; 
 int /*<<< orphan*/  MPMU_PCR_PJ ; 
 int MPMU_PCR_PJ_APBSD ; 
 int MPMU_PCR_PJ_AXISD ; 
 int MPMU_PCR_PJ_DDRCORSD ; 
 int MPMU_PCR_PJ_SLPEN ; 
 int MPMU_PCR_PJ_SPSD ; 
 int MPMU_PCR_PJ_VCTCXOSD ; 
#define  POWER_MODE_APPS_IDLE 133 
#define  POWER_MODE_APPS_SLEEP 132 
#define  POWER_MODE_CHIP_SLEEP 131 
#define  POWER_MODE_CORE_EXTIDLE 130 
#define  POWER_MODE_CORE_INTIDLE 129 
#define  POWER_MODE_SYS_SLEEP 128 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 

void mmp2_pm_enter_lowpower_mode(int state)
{
	uint32_t idle_cfg, apcr;

	idle_cfg = __raw_readl(APMU_PJ_IDLE_CFG);
	apcr = __raw_readl(MPMU_PCR_PJ);
	apcr &= ~(MPMU_PCR_PJ_SLPEN | MPMU_PCR_PJ_DDRCORSD | MPMU_PCR_PJ_APBSD
		 | MPMU_PCR_PJ_AXISD | MPMU_PCR_PJ_VCTCXOSD | (1 << 13));
	idle_cfg &= ~APMU_PJ_IDLE_CFG_PJ_IDLE;

	switch (state) {
	case POWER_MODE_SYS_SLEEP:
		apcr |= MPMU_PCR_PJ_SLPEN;		/* set the SLPEN bit */
		apcr |= MPMU_PCR_PJ_VCTCXOSD;		/* set VCTCXOSD */
		/* fall through */
	case POWER_MODE_CHIP_SLEEP:
		apcr |= MPMU_PCR_PJ_SLPEN;
		/* fall through */
	case POWER_MODE_APPS_SLEEP:
		apcr |= MPMU_PCR_PJ_APBSD;		/* set APBSD */
		/* fall through */
	case POWER_MODE_APPS_IDLE:
		apcr |= MPMU_PCR_PJ_AXISD;		/* set AXISDD bit */
		apcr |= MPMU_PCR_PJ_DDRCORSD;		/* set DDRCORSD bit */
		idle_cfg |= APMU_PJ_IDLE_CFG_PJ_PWRDWN;	/* PJ power down */
		apcr |= MPMU_PCR_PJ_SPSD;
		/* fall through */
	case POWER_MODE_CORE_EXTIDLE:
		idle_cfg |= APMU_PJ_IDLE_CFG_PJ_IDLE;	/* set the IDLE bit */
		idle_cfg &= ~APMU_PJ_IDLE_CFG_ISO_MODE_CNTRL_MASK;
		idle_cfg |= APMU_PJ_IDLE_CFG_PWR_SW(3)
			| APMU_PJ_IDLE_CFG_L2_PWR_SW;
		break;
	case POWER_MODE_CORE_INTIDLE:
		apcr &= ~MPMU_PCR_PJ_SPSD;
		break;
	}

	/* set reserve bits */
	apcr |= (1 << 30) | (1 << 25);

	/* finally write the registers back */
	__raw_writel(idle_cfg, APMU_PJ_IDLE_CFG);
	__raw_writel(apcr, MPMU_PCR_PJ);	/* 0xfe086000 */
}