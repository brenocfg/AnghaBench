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
struct mmc_softc {int /*<<< orphan*/  dev; } ;
struct mmc_ivars {int /*<<< orphan*/  vccq_180; int /*<<< orphan*/  vccq_120; } ;
typedef  enum mmc_bus_timing { ____Placeholder_mmc_bus_timing } mmc_bus_timing ;

/* Variables and functions */
 int MMC_ERR_INVALID ; 
 int MMC_ERR_NONE ; 
 scalar_t__ isset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mmcbr_set_vccq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mmcbr_switch_vccq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vccq_120 ; 
 int /*<<< orphan*/  vccq_180 ; 
 int /*<<< orphan*/  vccq_330 ; 

__attribute__((used)) static int
mmc_set_vccq(struct mmc_softc *sc, struct mmc_ivars *ivar,
    enum mmc_bus_timing timing)
{

	if (isset(&ivar->vccq_120, timing))
		mmcbr_set_vccq(sc->dev, vccq_120);
	else if (isset(&ivar->vccq_180, timing))
		mmcbr_set_vccq(sc->dev, vccq_180);
	else
		mmcbr_set_vccq(sc->dev, vccq_330);
	if (mmcbr_switch_vccq(sc->dev) != 0)
		return (MMC_ERR_INVALID);
	else
		return (MMC_ERR_NONE);
}