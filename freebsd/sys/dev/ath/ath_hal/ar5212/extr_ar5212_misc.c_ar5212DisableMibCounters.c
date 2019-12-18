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
struct ath_hal {int dummy; } ;

/* Variables and functions */
 int AR_MIBC ; 
 int AR_MIBC_CMC ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int,int) ; 

void 
ar5212DisableMibCounters(struct ath_hal *ah)
{
	OS_REG_WRITE(ah, AR_MIBC,  AR_MIBC | AR_MIBC_CMC);
}