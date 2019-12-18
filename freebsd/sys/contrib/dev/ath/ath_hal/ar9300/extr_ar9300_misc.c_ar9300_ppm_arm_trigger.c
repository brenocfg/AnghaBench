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
 int /*<<< orphan*/  AR_PHY_CHAN_INFO_MEMORY ; 
 int AR_PHY_CHAN_INFO_MEMORY_CAPTURE_MASK ; 
 int /*<<< orphan*/  AR_TSF_L32 ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 

u_int32_t
ar9300_ppm_arm_trigger(struct ath_hal *ah)
{
    u_int32_t val;
    u_int32_t ret;

    val = OS_REG_READ(ah, AR_PHY_CHAN_INFO_MEMORY);
    ret = OS_REG_READ(ah, AR_TSF_L32);
    OS_REG_WRITE(ah, AR_PHY_CHAN_INFO_MEMORY,
        val | AR_PHY_CHAN_INFO_MEMORY_CAPTURE_MASK);

    /* return low word of TSF at arm time */
    return ret;
}