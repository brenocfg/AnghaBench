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
typedef  int /*<<< orphan*/  u_int ;
struct ath_hal {int dummy; } ;
struct ath_desc {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_11N_RATE_SERIES ;

/* Variables and functions */
 int /*<<< orphan*/  ar9300_set_11n_rate_scenario (struct ath_hal*,void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ar9300_freebsd_set_11n_rate_scenario(struct ath_hal *ah, struct ath_desc *ds,
    u_int durUpdateEn, u_int rtsctsRate, HAL_11N_RATE_SERIES series[],
    u_int nseries, u_int flags)
{

	/* lastds=NULL, rtscts_duration is 0, smart antenna is 0 */
	ar9300_set_11n_rate_scenario(ah, (void *) ds, (void *)ds, durUpdateEn,
	    rtsctsRate, 0, series, nseries, flags, 0);
}