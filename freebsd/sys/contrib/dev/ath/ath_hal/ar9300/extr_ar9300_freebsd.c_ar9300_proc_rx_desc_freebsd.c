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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ath_rx_status {int dummy; } ;
struct ath_hal {int dummy; } ;
struct ath_desc {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ar9300_proc_rx_desc_fast (struct ath_hal*,struct ath_desc*,int /*<<< orphan*/ ,struct ath_desc*,struct ath_rx_status*,void*) ; 

HAL_STATUS
ar9300_proc_rx_desc_freebsd(struct ath_hal *ah, struct ath_desc *ds,
    uint32_t pa, struct ath_desc *ds_next, uint64_t tsf,
    struct ath_rx_status *rxs)
{

	return (ar9300_proc_rx_desc_fast(ah, ds, 0, ds_next, rxs,
	    (void *) ds));
}