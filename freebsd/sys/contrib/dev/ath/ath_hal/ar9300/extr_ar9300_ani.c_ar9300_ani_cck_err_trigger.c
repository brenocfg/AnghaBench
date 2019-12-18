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
struct ar9300_ani_state {scalar_t__ cck_noise_immunity_level; } ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  DO_ANI (struct ath_hal*) ; 
 scalar_t__ HAL_ANI_CCK_MAX_LEVEL ; 
 int /*<<< orphan*/  ar9300_ani_set_cck_noise_immunity_level (struct ath_hal*,scalar_t__) ; 

__attribute__((used)) static void
ar9300_ani_cck_err_trigger(struct ath_hal *ah)
{
    struct ath_hal_9300 *ahp = AH9300(ah);
    struct ar9300_ani_state *ani_state;

    if (!DO_ANI(ah)) {
        return;
    }

    ani_state = ahp->ah_curani;

    if (ani_state->cck_noise_immunity_level < HAL_ANI_CCK_MAX_LEVEL) {
        ar9300_ani_set_cck_noise_immunity_level(
            ah, ani_state->cck_noise_immunity_level + 1);
    }
}