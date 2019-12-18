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
typedef  int /*<<< orphan*/  u_int8_t ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_CCA_0 ; 
 int /*<<< orphan*/  AR_PHY_CCA_THRESH62 ; 
 int /*<<< orphan*/  AR_PHY_EXT_CCA ; 
 int /*<<< orphan*/  AR_PHY_EXT_CCA0 ; 
 int /*<<< orphan*/  AR_PHY_EXT_CCA0_THRESH62 ; 
 int /*<<< orphan*/  AR_PHY_EXT_CCA_THRESH62 ; 
 int /*<<< orphan*/  OS_REG_RMW_FIELD (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ar9300_set_cca_threshold(struct ath_hal *ah, u_int8_t thresh62)
{
    OS_REG_RMW_FIELD(ah, AR_PHY_CCA_0, AR_PHY_CCA_THRESH62, thresh62);
    OS_REG_RMW_FIELD(ah, AR_PHY_EXT_CCA0, AR_PHY_EXT_CCA0_THRESH62, thresh62);
    /*
    OS_REG_RMW_FIELD(ah,
        AR_PHY_EXTCHN_PWRTHR1, AR_PHY_EXT_CCA0_THRESH62, thresh62);
     */
    OS_REG_RMW_FIELD(ah, AR_PHY_EXT_CCA, AR_PHY_EXT_CCA_THRESH62, thresh62);
}