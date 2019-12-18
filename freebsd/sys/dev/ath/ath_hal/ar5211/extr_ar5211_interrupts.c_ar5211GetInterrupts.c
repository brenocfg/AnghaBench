#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ath_hal {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ah_maskReg; } ;
typedef  int /*<<< orphan*/  HAL_INT ;

/* Variables and functions */
 TYPE_1__* AH5211 (struct ath_hal*) ; 

HAL_INT
ar5211GetInterrupts(struct ath_hal *ah)
{
	return AH5211(ah)->ah_maskReg;
}