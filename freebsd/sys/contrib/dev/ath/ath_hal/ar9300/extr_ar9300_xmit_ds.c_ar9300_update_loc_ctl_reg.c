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
typedef  int u_int32_t ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_LOC_CTL_REG ; 
 int AR_LOC_CTL_REG_FS ; 
 int /*<<< orphan*/  AR_LOC_TIMER_REG ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 

void ar9300_update_loc_ctl_reg(struct ath_hal *ah, int pos_bit)
{
    u_int32_t reg_val;
    reg_val = OS_REG_READ(ah, AR_LOC_CTL_REG);
    if (pos_bit) {
        if (!(reg_val & AR_LOC_CTL_REG_FS)) {
            /* set fast timestamp bit in the regiter */
            OS_REG_WRITE(ah, AR_LOC_CTL_REG, (reg_val | AR_LOC_CTL_REG_FS));
            OS_REG_WRITE(ah, AR_LOC_TIMER_REG, 0);
        }
    }
    else {
        OS_REG_WRITE(ah, AR_LOC_CTL_REG, (reg_val & ~AR_LOC_CTL_REG_FS));
    }
}