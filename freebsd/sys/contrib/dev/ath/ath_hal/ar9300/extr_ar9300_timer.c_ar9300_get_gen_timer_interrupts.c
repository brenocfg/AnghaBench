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
typedef  int /*<<< orphan*/  u_int32_t ;
struct ath_hal_9300 {int /*<<< orphan*/  ah_intr_gen_timer_thresh; int /*<<< orphan*/  ah_intr_gen_timer_trigger; } ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 

void
ar9300_get_gen_timer_interrupts(
    struct ath_hal *ah,
    u_int32_t *trigger,
    u_int32_t *thresh)
{
    struct ath_hal_9300 *ahp = AH9300(ah);
    *trigger = ahp->ah_intr_gen_timer_trigger;
    *thresh = ahp->ah_intr_gen_timer_thresh;
}