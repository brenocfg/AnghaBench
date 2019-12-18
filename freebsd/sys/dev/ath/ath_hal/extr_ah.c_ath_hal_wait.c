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
typedef  int /*<<< orphan*/  u_int ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_TIMEOUT ; 
 int /*<<< orphan*/  ath_hal_waitfor (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HAL_BOOL
ath_hal_wait(struct ath_hal *ah, u_int reg, uint32_t mask, uint32_t val)
{
#define	AH_TIMEOUT	5000
	return ath_hal_waitfor(ah, reg, mask, val, AH_TIMEOUT);
#undef AH_TIMEOUT
}