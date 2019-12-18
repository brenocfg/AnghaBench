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
typedef  int /*<<< orphan*/  u_int32_t ;
struct ath_hal {int dummy; } ;
struct TYPE_2__ {int mode_mask; int /*<<< orphan*/  mode_addr; int /*<<< orphan*/  period_addr; int /*<<< orphan*/  next_addr; } ;

/* Variables and functions */
 int AR_FIRST_NDP_TIMER ; 
 int /*<<< orphan*/  AR_GENTMR_BIT (int) ; 
 int AR_GEN_TIMER_BANK_1_LEN ; 
 int /*<<< orphan*/  AR_IMR_S5 ; 
 int /*<<< orphan*/  AR_IMR_S5_GENTIMER_THRESH ; 
 int /*<<< orphan*/  AR_IMR_S5_GENTIMER_TRIG ; 
 int /*<<< orphan*/  AR_MAC_PCU_GEN_TIMER_TSF_SEL ; 
 int AR_NUM_GEN_TIMERS ; 
 scalar_t__ AR_SREV_APHRODITE (struct ath_hal*) ; 
 scalar_t__ AR_SREV_JUPITER (struct ath_hal*) ; 
 int /*<<< orphan*/  OS_REG_CLR_BIT (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OS_REG_SET_BIT (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* gen_timer_configuration ; 

void
ar9300_start_generic_timer(
    struct ath_hal *ah,
    int index,
    u_int32_t timer_next,
    u_int32_t timer_period)
{
    if ((index < AR_FIRST_NDP_TIMER) || (index >= AR_NUM_GEN_TIMERS)) {
        return;
    }

    /*
     * Program generic timer registers
     */
    OS_REG_WRITE(ah, gen_timer_configuration[index].next_addr, timer_next);
    OS_REG_WRITE(ah, gen_timer_configuration[index].period_addr, timer_period);
    OS_REG_SET_BIT(ah,
        gen_timer_configuration[index].mode_addr,
        gen_timer_configuration[index].mode_mask);

    if (AR_SREV_JUPITER(ah) || AR_SREV_APHRODITE(ah)) {
        /*
         * Starting from Jupiter, each generic timer can select which tsf to
         * use. But we still follow the old rule, 0 - 7 use tsf and 8 - 15
         * use tsf2.
         */
        if ((index < AR_GEN_TIMER_BANK_1_LEN)) {
            OS_REG_CLR_BIT(ah, AR_MAC_PCU_GEN_TIMER_TSF_SEL, (1 << index));
        }
        else {
            OS_REG_SET_BIT(ah, AR_MAC_PCU_GEN_TIMER_TSF_SEL, (1 << index));
        }
    }

    /* Enable both trigger and thresh interrupt masks */
    OS_REG_SET_BIT(ah, AR_IMR_S5,
                   (SM(AR_GENTMR_BIT(index), AR_IMR_S5_GENTIMER_THRESH) |
                    SM(AR_GENTMR_BIT(index), AR_IMR_S5_GENTIMER_TRIG)));
}