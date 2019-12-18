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
struct ath_hal {int dummy; } ;
typedef  scalar_t__ HAL_RX_QUEUE ;

/* Variables and functions */
 int /*<<< orphan*/  AR_RXDP ; 
 int /*<<< orphan*/  HALASSERT (int) ; 
 scalar_t__ HAL_RX_QUEUE_HP ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ar5210SetRxDP(struct ath_hal *ah, uint32_t rxdp, HAL_RX_QUEUE qtype)
{

	HALASSERT(qtype == HAL_RX_QUEUE_HP);
	OS_REG_WRITE(ah, AR_RXDP, rxdp);
}