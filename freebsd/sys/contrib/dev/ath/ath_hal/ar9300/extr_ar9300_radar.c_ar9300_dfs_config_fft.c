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
struct ath_hal {int dummy; } ;
typedef  scalar_t__ HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_RADAR_0 ; 
 int /*<<< orphan*/  AR_PHY_RADAR_0_FFT_ENA ; 
 int /*<<< orphan*/  OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u_int32_t ar9300_dfs_config_fft(struct ath_hal *ah, HAL_BOOL is_enable)
{
    u_int32_t val;

    val = OS_REG_READ(ah, AR_PHY_RADAR_0);

    if (is_enable) {
        val |= AR_PHY_RADAR_0_FFT_ENA;
    } else {
        val &= ~AR_PHY_RADAR_0_FFT_ENA;
    }

    OS_REG_WRITE(ah, AR_PHY_RADAR_0, val);
    val = OS_REG_READ(ah, AR_PHY_RADAR_0);
    return val;
}