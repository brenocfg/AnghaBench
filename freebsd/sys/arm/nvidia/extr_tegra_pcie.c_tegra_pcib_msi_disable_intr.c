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
struct tegra_pcib_softc {int dummy; } ;
struct tegra_pcib_irqsrc {int dummy; } ;
struct intr_irqsrc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct tegra_pcib_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_pcib_isrc_mask (struct tegra_pcib_softc*,struct tegra_pcib_irqsrc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tegra_pcib_msi_disable_intr(device_t dev, struct intr_irqsrc *isrc)
{
	struct tegra_pcib_softc *sc;
	struct tegra_pcib_irqsrc *tgi;

	sc = device_get_softc(dev);
	tgi = (struct tegra_pcib_irqsrc *)isrc;
	tegra_pcib_isrc_mask(sc, tgi, 0);
}