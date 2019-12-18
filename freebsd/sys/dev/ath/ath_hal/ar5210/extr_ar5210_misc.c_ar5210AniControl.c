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
typedef  int /*<<< orphan*/  HAL_BOOL ;
typedef  int /*<<< orphan*/  HAL_ANI_CMD ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 

HAL_BOOL
ar5210AniControl(struct ath_hal *ah, HAL_ANI_CMD cmd, int param)
{
	return AH_FALSE;
}