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
typedef  int uint64_t ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_TSF_L32 ; 
 int /*<<< orphan*/  AR_TSF_U32 ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 

void
ar5212SetTsf64(struct ath_hal *ah, uint64_t tsf64)
{
	OS_REG_WRITE(ah, AR_TSF_L32, tsf64 & 0xffffffff);
	OS_REG_WRITE(ah, AR_TSF_U32, (tsf64 >> 32) & 0xffffffff);
}