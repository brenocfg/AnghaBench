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
typedef  scalar_t__ HAL_RX_QUEUE ;

/* Variables and functions */
 int /*<<< orphan*/  AR_RXDP ; 
 int /*<<< orphan*/  HALASSERT (int) ; 
 scalar_t__ HAL_RX_QUEUE_HP ; 
 scalar_t__ OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,scalar_t__) ; 

void
ar5211SetRxDP(struct ath_hal *ah, uint32_t rxdp, HAL_RX_QUEUE qtype)
{

	HALASSERT(qtype == HAL_RX_QUEUE_HP);
	OS_REG_WRITE(ah, AR_RXDP, rxdp);
	HALASSERT(OS_REG_READ(ah, AR_RXDP) == rxdp);
}