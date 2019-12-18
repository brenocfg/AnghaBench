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
struct ath_hal {int dummy; } ;
struct TYPE_2__ {int mode_mask; int /*<<< orphan*/  mode_addr; } ;

/* Variables and functions */
 int AR_FIRST_NDP_TIMER ; 
 int /*<<< orphan*/  AR_GENTMR_BIT (int) ; 
 int /*<<< orphan*/  AR_IMR_S5 ; 
 int /*<<< orphan*/  AR_IMR_S5_GENTIMER_THRESH ; 
 int /*<<< orphan*/  AR_IMR_S5_GENTIMER_TRIG ; 
 int AR_NUM_GEN_TIMERS ; 
 int /*<<< orphan*/  OS_REG_CLR_BIT (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int SM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* gen_timer_configuration ; 

void
ar9300_stop_generic_timer(struct ath_hal *ah, int index)
{
    if ((index < AR_FIRST_NDP_TIMER) || (index >= AR_NUM_GEN_TIMERS)) {
        return;
    }

    /*
     * Clear generic timer enable bits.
     */
    OS_REG_CLR_BIT(ah,
        gen_timer_configuration[index].mode_addr,
        gen_timer_configuration[index].mode_mask);

    /* Disable both trigger and thresh interrupt masks */
    OS_REG_CLR_BIT(ah, AR_IMR_S5,
                   (SM(AR_GENTMR_BIT(index), AR_IMR_S5_GENTIMER_THRESH) |
                    SM(AR_GENTMR_BIT(index), AR_IMR_S5_GENTIMER_TRIG)));
}