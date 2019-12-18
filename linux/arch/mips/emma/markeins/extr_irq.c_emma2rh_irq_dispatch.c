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
typedef  unsigned long u32 ;

/* Variables and functions */
 int /*<<< orphan*/  EMMA2RH_BHIF_INT_EN_0 ; 
 int /*<<< orphan*/  EMMA2RH_BHIF_INT_EN_1 ; 
 int /*<<< orphan*/  EMMA2RH_BHIF_INT_EN_2 ; 
 int /*<<< orphan*/  EMMA2RH_BHIF_INT_ST_0 ; 
 int /*<<< orphan*/  EMMA2RH_BHIF_INT_ST_1 ; 
 int /*<<< orphan*/  EMMA2RH_BHIF_INT_ST_2 ; 
 int /*<<< orphan*/  EMMA2RH_BHIF_SW_INT ; 
 int /*<<< orphan*/  EMMA2RH_BHIF_SW_INT_EN ; 
 int EMMA2RH_GPIO_CASCADE ; 
 int /*<<< orphan*/  EMMA2RH_GPIO_INT_MASK ; 
 int /*<<< orphan*/  EMMA2RH_GPIO_INT_ST ; 
 scalar_t__ EMMA2RH_GPIO_IRQ_BASE ; 
 scalar_t__ EMMA2RH_IRQ_BASE ; 
 unsigned long EMMA2RH_SW_CASCADE ; 
 scalar_t__ EMMA2RH_SW_IRQ_BASE ; 
 int /*<<< orphan*/  do_IRQ (scalar_t__) ; 
 unsigned long emma2rh_in32 (int /*<<< orphan*/ ) ; 

void emma2rh_irq_dispatch(void)
{
	u32 intStatus;
	u32 bitmask;
	u32 i;

	intStatus = emma2rh_in32(EMMA2RH_BHIF_INT_ST_0) &
		    emma2rh_in32(EMMA2RH_BHIF_INT_EN_0);

#ifdef EMMA2RH_SW_CASCADE
	if (intStatus & (1UL << EMMA2RH_SW_CASCADE)) {
		u32 swIntStatus;
		swIntStatus = emma2rh_in32(EMMA2RH_BHIF_SW_INT)
		    & emma2rh_in32(EMMA2RH_BHIF_SW_INT_EN);
		for (i = 0, bitmask = 1; i < 32; i++, bitmask <<= 1) {
			if (swIntStatus & bitmask) {
				do_IRQ(EMMA2RH_SW_IRQ_BASE + i);
				return;
			}
		}
	}
	/* Skip S/W interrupt */
	intStatus &= ~(1UL << EMMA2RH_SW_CASCADE);
#endif

	for (i = 0, bitmask = 1; i < 32; i++, bitmask <<= 1) {
		if (intStatus & bitmask) {
			do_IRQ(EMMA2RH_IRQ_BASE + i);
			return;
		}
	}

	intStatus = emma2rh_in32(EMMA2RH_BHIF_INT_ST_1) &
		    emma2rh_in32(EMMA2RH_BHIF_INT_EN_1);

#ifdef EMMA2RH_GPIO_CASCADE
	if (intStatus & (1UL << (EMMA2RH_GPIO_CASCADE % 32))) {
		u32 gpioIntStatus;
		gpioIntStatus = emma2rh_in32(EMMA2RH_GPIO_INT_ST)
		    & emma2rh_in32(EMMA2RH_GPIO_INT_MASK);
		for (i = 0, bitmask = 1; i < 32; i++, bitmask <<= 1) {
			if (gpioIntStatus & bitmask) {
				do_IRQ(EMMA2RH_GPIO_IRQ_BASE + i);
				return;
			}
		}
	}
	/* Skip GPIO interrupt */
	intStatus &= ~(1UL << (EMMA2RH_GPIO_CASCADE % 32));
#endif

	for (i = 32, bitmask = 1; i < 64; i++, bitmask <<= 1) {
		if (intStatus & bitmask) {
			do_IRQ(EMMA2RH_IRQ_BASE + i);
			return;
		}
	}

	intStatus = emma2rh_in32(EMMA2RH_BHIF_INT_ST_2) &
		    emma2rh_in32(EMMA2RH_BHIF_INT_EN_2);

	for (i = 64, bitmask = 1; i < 96; i++, bitmask <<= 1) {
		if (intStatus & bitmask) {
			do_IRQ(EMMA2RH_IRQ_BASE + i);
			return;
		}
	}
}