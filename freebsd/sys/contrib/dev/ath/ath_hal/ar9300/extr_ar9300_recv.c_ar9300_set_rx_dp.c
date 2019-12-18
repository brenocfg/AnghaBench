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
 int /*<<< orphan*/  HALASSERT (int) ; 
 scalar_t__ HAL_RX_QUEUE_HP ; 
 scalar_t__ HAL_RX_QUEUE_LP ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ar9300_set_rx_dp(struct ath_hal *ah, u_int32_t rxdp, HAL_RX_QUEUE qtype)
{
    HALASSERT((qtype == HAL_RX_QUEUE_HP) || (qtype == HAL_RX_QUEUE_LP));

    if (qtype == HAL_RX_QUEUE_HP) {
        OS_REG_WRITE(ah, AR_HP_RXDP, rxdp);
    } else {
        OS_REG_WRITE(ah, AR_LP_RXDP, rxdp);
    }
}