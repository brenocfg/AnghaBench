#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ath_softc {int /*<<< orphan*/  sc_ah; } ;
struct TYPE_4__ {scalar_t__ pe_enabled; } ;
typedef  TYPE_1__ HAL_PHYERR_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  ath_hal_enabledfs (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ath_hal_getdfsthresh (int /*<<< orphan*/ ,TYPE_1__*) ; 

int
ath_dfs_radar_disable(struct ath_softc *sc)
{
#if 1
	HAL_PHYERR_PARAM pe;

	(void) ath_hal_getdfsthresh(sc->sc_ah, &pe);
	pe.pe_enabled = 0;
	(void) ath_hal_enabledfs(sc->sc_ah, &pe);
	return (0);
#else
	return (0);
#endif
}