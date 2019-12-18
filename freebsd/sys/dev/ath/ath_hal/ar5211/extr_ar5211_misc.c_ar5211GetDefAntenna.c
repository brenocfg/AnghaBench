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
typedef  int u_int ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_DEF_ANTENNA ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 

u_int
ar5211GetDefAntenna(struct ath_hal *ah)
{   
	return (OS_REG_READ(ah, AR_DEF_ANTENNA) & 0x7);
}