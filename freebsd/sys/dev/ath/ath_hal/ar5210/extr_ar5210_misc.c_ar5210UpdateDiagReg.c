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

/* Variables and functions */
 int /*<<< orphan*/  AR_DIAG_SW ; 
 int /*<<< orphan*/  AR_DIAG_SW_DIS_CRYPTO ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ar5210UpdateDiagReg(struct ath_hal *ah, uint32_t val)
{

	/* Disable all hardware encryption */
	val |= AR_DIAG_SW_DIS_CRYPTO;
	OS_REG_WRITE(ah, AR_DIAG_SW, val);
}