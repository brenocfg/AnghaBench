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
typedef  scalar_t__ uint32_t ;
struct ath_hal {int dummy; } ;
typedef  scalar_t__ HAL_HT_MACMODE ;

/* Variables and functions */
 scalar_t__ AR_2040_JOINED_RX_CLEAR ; 
 int /*<<< orphan*/  AR_2040_MODE ; 
 scalar_t__ HAL_HT_MACMODE_2040 ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,scalar_t__) ; 

void
ar5416Set11nMac2040(struct ath_hal *ah, HAL_HT_MACMODE mode)
{
    uint32_t macmode;

    /* Configure MAC for 20/40 operation */
    if (mode == HAL_HT_MACMODE_2040) {
        macmode = AR_2040_JOINED_RX_CLEAR;
    } else {
        macmode = 0;
    }
    OS_REG_WRITE(ah, AR_2040_MODE, macmode);
}