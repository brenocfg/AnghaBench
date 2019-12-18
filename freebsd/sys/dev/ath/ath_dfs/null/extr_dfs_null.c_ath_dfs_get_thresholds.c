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
struct ath_softc {int /*<<< orphan*/  sc_ah; } ;
typedef  int /*<<< orphan*/  HAL_PHYERR_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  ath_hal_getdfsthresh (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
ath_dfs_get_thresholds(struct ath_softc *sc, HAL_PHYERR_PARAM *param)
{
	ath_hal_getdfsthresh(sc->sc_ah, param);
	return (1);
}