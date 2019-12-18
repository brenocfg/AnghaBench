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

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_RADAR_DC_PWR_THRESH ; 
 int /*<<< orphan*/  AR_PHY_RADAR_EXT ; 
 int /*<<< orphan*/  MAX_RADAR_DC_PWR_THRESH ; 
 int /*<<< orphan*/  OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ar9300_set_radar_dc_thresh(struct ath_hal *ah)
{
    u_int32_t val;
    val = OS_REG_READ(ah, AR_PHY_RADAR_EXT);
    val &= ~AR_PHY_RADAR_DC_PWR_THRESH;
    val |= SM(MAX_RADAR_DC_PWR_THRESH, AR_PHY_RADAR_DC_PWR_THRESH);
    OS_REG_WRITE(ah, AR_PHY_RADAR_EXT, val);

    val = OS_REG_READ(ah, AR_PHY_RADAR_EXT);
}