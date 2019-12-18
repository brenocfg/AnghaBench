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
struct ath_desc {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 

HAL_BOOL
ar9300_freebsd_setup_last_tx_desc(struct ath_hal *ah, struct ath_desc *ds,
    const struct ath_desc *ds0)
{

//	ath_hal_printf(ah, "%s: called\n", __func__);
	return AH_FALSE;
}