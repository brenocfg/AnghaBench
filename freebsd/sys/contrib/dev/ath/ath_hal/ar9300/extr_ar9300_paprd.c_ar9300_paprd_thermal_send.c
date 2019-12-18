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
 scalar_t__ AR_SREV_HORNET (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_TFCNT ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 

int ar9300_paprd_thermal_send(struct ath_hal *ah)
{
    if (AR_SREV_HORNET(ah)) {
        return OS_REG_READ(ah, AR_TFCNT);
    } else {
        return 1;
    }
}