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
typedef  int /*<<< orphan*/  uint64_t ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_TIMER0 ; 
 int /*<<< orphan*/  OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TU_TO_TSF (int /*<<< orphan*/ ) ; 

uint64_t
ar5210GetNextTBTT(struct ath_hal *ah)
{
#define TU_TO_TSF(_tu)	(((uint64_t)(_tu)) << 10)
	return TU_TO_TSF(OS_REG_READ(ah, AR_TIMER0));
#undef TU_TO_TSF
}