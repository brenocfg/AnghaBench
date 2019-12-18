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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  RTL8366S_GREEN_FEATURE_REG ; 
 int /*<<< orphan*/  RTL8366S_GREEN_FEATURE_RX_BIT ; 
 int /*<<< orphan*/  RTL8366S_GREEN_FEATURE_TX_BIT ; 
 scalar_t__ rtl8366_setRegisterBit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rtl8366s_setGreenFeature(uint32_t tx, uint32_t rx)
{
    if (rtl8366_setRegisterBit(RTL8366S_GREEN_FEATURE_REG,
                               RTL8366S_GREEN_FEATURE_TX_BIT, tx))
        return -1;

    if (rtl8366_setRegisterBit(RTL8366S_GREEN_FEATURE_REG,
                               RTL8366S_GREEN_FEATURE_RX_BIT, rx))
        return -1;

    return 0;
}