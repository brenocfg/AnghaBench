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
struct ar9300_ani_state {scalar_t__ cck_phy_err_count; scalar_t__ ofdm_phy_err_count; scalar_t__ listen_time; } ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_PHY_ERR_1 ; 
 int /*<<< orphan*/  AR_PHY_ERR_2 ; 
 int /*<<< orphan*/  AR_PHY_ERR_CCK_TIMING ; 
 int /*<<< orphan*/  AR_PHY_ERR_MASK_1 ; 
 int /*<<< orphan*/  AR_PHY_ERR_MASK_2 ; 
 int /*<<< orphan*/  AR_PHY_ERR_OFDM_TIMING ; 
 int /*<<< orphan*/  DO_ANI (struct ath_hal*) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9300_update_mib_mac_stats (struct ath_hal*) ; 

__attribute__((used)) static void
ar9300_ani_restart(struct ath_hal *ah)
{
    struct ath_hal_9300 *ahp = AH9300(ah);
    struct ar9300_ani_state *ani_state;

    if (!DO_ANI(ah)) {
        return;
    }

    ani_state = ahp->ah_curani;

    ani_state->listen_time = 0;

    OS_REG_WRITE(ah, AR_PHY_ERR_1, 0);
    OS_REG_WRITE(ah, AR_PHY_ERR_2, 0);
    OS_REG_WRITE(ah, AR_PHY_ERR_MASK_1, AR_PHY_ERR_OFDM_TIMING);
    OS_REG_WRITE(ah, AR_PHY_ERR_MASK_2, AR_PHY_ERR_CCK_TIMING);

    /* Clear the mib counters and save them in the stats */
    ar9300_update_mib_mac_stats(ah);

    ani_state->ofdm_phy_err_count = 0;
    ani_state->cck_phy_err_count = 0;
}