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
struct ath_hal_9300 {int /*<<< orphan*/  ah_avail_gen_timers; } ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_GENTMR_BIT (int) ; 
 int /*<<< orphan*/  ar9300_stop_generic_timer (struct ath_hal*,int) ; 

void
ar9300_free_generic_timer(struct ath_hal *ah, int index)
{
    struct ath_hal_9300 *ahp = AH9300(ah);

    ar9300_stop_generic_timer(ah, index);
    ahp->ah_avail_gen_timers |= AR_GENTMR_BIT(index);
}