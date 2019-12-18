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
 int /*<<< orphan*/  AR_PHY_FIND_SIG ; 
 int /*<<< orphan*/  AR_PHY_FIND_SIG_FIRPWR ; 
 int /*<<< orphan*/  AR_PHY_FIND_SIG_FIRPWR_SIGN_BIT ; 
 int /*<<< orphan*/  AR_PHY_FIND_SIG_FIRSTEP ; 
 int /*<<< orphan*/  AR_PHY_FIND_SIG_LOW ; 
 int /*<<< orphan*/  AR_PHY_FIND_SIG_LOW_FIRPWR ; 
 int /*<<< orphan*/  AR_PHY_FIND_SIG_LOW_FIRPWR_SIGN_BIT ; 
 int /*<<< orphan*/  AR_PHY_FIND_SIG_LOW_FIRSTEP_LOW ; 
 int /*<<< orphan*/  AR_PHY_FIND_SIG_LOW_RELSTEP ; 
 int /*<<< orphan*/  AR_PHY_FIND_SIG_LOW_RELSTEP_SIGN_BIT ; 
 int /*<<< orphan*/  AR_PHY_FIND_SIG_RELPWR ; 
 int /*<<< orphan*/  AR_PHY_FIND_SIG_RELPWR_SIGN_BIT ; 
 int /*<<< orphan*/  AR_PHY_FIND_SIG_RELSTEP ; 
 int /*<<< orphan*/  AR_PHY_FIND_SIG_RELSTEP_SIGN_BIT ; 
 int /*<<< orphan*/  OS_REG_CLR_BIT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_RMW_FIELD (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
ar9300_disable_weak_signal(struct ath_hal *ah)
{
    /* set firpwr to max (signed) */
    OS_REG_RMW_FIELD(ah, AR_PHY_FIND_SIG, AR_PHY_FIND_SIG_FIRPWR, 0x7f);
    OS_REG_CLR_BIT(ah, AR_PHY_FIND_SIG, AR_PHY_FIND_SIG_FIRPWR_SIGN_BIT);

    /* set firstep to max */
    OS_REG_RMW_FIELD(ah, AR_PHY_FIND_SIG, AR_PHY_FIND_SIG_FIRSTEP, 0x3f);

    /* set relpwr to max (signed) */
    OS_REG_RMW_FIELD(ah, AR_PHY_FIND_SIG, AR_PHY_FIND_SIG_RELPWR, 0x1f);
    OS_REG_CLR_BIT(ah, AR_PHY_FIND_SIG, AR_PHY_FIND_SIG_RELPWR_SIGN_BIT);

    /* set relstep to max (signed) */
    OS_REG_RMW_FIELD(ah, AR_PHY_FIND_SIG, AR_PHY_FIND_SIG_RELSTEP, 0x1f);
    OS_REG_CLR_BIT(ah, AR_PHY_FIND_SIG, AR_PHY_FIND_SIG_RELSTEP_SIGN_BIT);
 
    /* set firpwr_low to max (signed) */
    OS_REG_RMW_FIELD(ah, AR_PHY_FIND_SIG_LOW, AR_PHY_FIND_SIG_LOW_FIRPWR, 0x7f);
    OS_REG_CLR_BIT(
        ah, AR_PHY_FIND_SIG_LOW, AR_PHY_FIND_SIG_LOW_FIRPWR_SIGN_BIT);

    /* set firstep_low to max */
    OS_REG_RMW_FIELD(
        ah, AR_PHY_FIND_SIG_LOW, AR_PHY_FIND_SIG_LOW_FIRSTEP_LOW, 0x3f);

    /* set relstep_low to max (signed) */
    OS_REG_RMW_FIELD(
        ah, AR_PHY_FIND_SIG_LOW, AR_PHY_FIND_SIG_LOW_RELSTEP, 0x1f);
    OS_REG_CLR_BIT(
        ah, AR_PHY_FIND_SIG_LOW, AR_PHY_FIND_SIG_LOW_RELSTEP_SIGN_BIT);
}