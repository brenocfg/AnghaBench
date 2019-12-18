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
typedef  scalar_t__ HAL_RX_QUEUE ;

/* Variables and functions */
 int /*<<< orphan*/  AR_HP_RXDP ; 
 int /*<<< orphan*/  AR_LP_RXDP ; 
 scalar_t__ HAL_RX_QUEUE_HP ; 
 int /*<<< orphan*/  OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 

u_int32_t
ar9300_get_rx_dp(struct ath_hal *ath, HAL_RX_QUEUE qtype)
{
    if (qtype == HAL_RX_QUEUE_HP) {
        return OS_REG_READ(ath, AR_HP_RXDP);
    } else {
        return OS_REG_READ(ath, AR_LP_RXDP);
    }
}