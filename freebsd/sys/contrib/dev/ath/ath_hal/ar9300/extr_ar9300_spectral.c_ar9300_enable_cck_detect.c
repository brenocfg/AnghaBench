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
struct ath_hal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_MODE ; 
 int /*<<< orphan*/  AR_PHY_MODE_DISABLE_CCK ; 
 int /*<<< orphan*/  AR_PHY_MODE_DYNAMIC ; 
 int /*<<< orphan*/  OS_REG_RMW_FIELD (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void ar9300_enable_cck_detect(struct ath_hal *ah)
{
    OS_REG_RMW_FIELD(ah, AR_PHY_MODE, AR_PHY_MODE_DISABLE_CCK, 0);
    OS_REG_RMW_FIELD(ah, AR_PHY_MODE, AR_PHY_MODE_DYNAMIC, 1);
}