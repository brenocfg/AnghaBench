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
struct ath_tx_status {int dummy; } ;
struct ath_hal {int dummy; } ;
struct ath_desc {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ar9300_proc_tx_desc (struct ath_hal*,struct ath_tx_status*) ; 

HAL_STATUS
ar9300_freebsd_proc_tx_desc(struct ath_hal *ah, struct ath_desc *ds,
    struct ath_tx_status *ts)
{

	return ar9300_proc_tx_desc(ah, ts);
}