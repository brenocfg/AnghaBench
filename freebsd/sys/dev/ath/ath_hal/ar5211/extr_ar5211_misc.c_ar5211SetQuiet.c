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
typedef  int /*<<< orphan*/  HAL_STATUS ;
typedef  int /*<<< orphan*/  HAL_QUIET_FLAG ;

/* Variables and functions */
 int /*<<< orphan*/  HAL_OK ; 

HAL_STATUS
ar5211SetQuiet(struct ath_hal *ah, uint32_t period, uint32_t duration,
    uint32_t next_start, HAL_QUIET_FLAG flags)
{
	return HAL_OK;
}