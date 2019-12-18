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
struct ath_hal_9300 {struct ar9300_ani_state* ah_curani; } ;
struct ath_hal {int dummy; } ;
struct ar9300_ani_state {int /*<<< orphan*/  phy_noise_spur; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 

HAL_BOOL
ar9300_is_ani_noise_spur(struct ath_hal *ah)
{
    struct ath_hal_9300 *ahp = AH9300(ah);
    struct ar9300_ani_state *ani_state;

    ani_state = ahp->ah_curani;

    return ani_state->phy_noise_spur;
}