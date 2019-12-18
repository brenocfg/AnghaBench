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
typedef  int uint32_t ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_RESET_TSF ; 
 int /*<<< orphan*/  AR_RESET_TSF_ONCE ; 
 int /*<<< orphan*/  AR_SLP32_MODE ; 
 int AR_SLP32_TSF_WRITE_STATUS ; 
 int /*<<< orphan*/  OS_DELAY (int) ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ar5416ResetTsf(struct ath_hal *ah)
{
	uint32_t v;
	int i;

	for (i = 0; i < 10; i++) {
		v = OS_REG_READ(ah, AR_SLP32_MODE);
		if ((v & AR_SLP32_TSF_WRITE_STATUS) == 0)
			break;
		OS_DELAY(10);
	}
	OS_REG_WRITE(ah, AR_RESET_TSF, AR_RESET_TSF_ONCE);	
}