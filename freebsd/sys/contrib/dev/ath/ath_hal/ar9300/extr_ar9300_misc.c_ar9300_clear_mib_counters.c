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
typedef  int u_int32_t ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_MIBC ; 
 int AR_MIBC_CMC ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 

void
ar9300_clear_mib_counters(struct ath_hal *ah)
{
    u_int32_t reg_val;

    reg_val = OS_REG_READ(ah, AR_MIBC);
    OS_REG_WRITE(ah, AR_MIBC, reg_val | AR_MIBC_CMC);
    OS_REG_WRITE(ah, AR_MIBC, reg_val & ~AR_MIBC_CMC);
}