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
struct tegra_gpio_softc {int dummy; } ;
struct tegra_gpio_irqsrc {int dummy; } ;
struct intr_irqsrc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct tegra_gpio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_gpio_isrc_eoi (struct tegra_gpio_softc*,struct tegra_gpio_irqsrc*) ; 
 scalar_t__ tegra_gpio_isrc_is_level (struct tegra_gpio_irqsrc*) ; 
 int /*<<< orphan*/  tegra_gpio_isrc_mask (struct tegra_gpio_softc*,struct tegra_gpio_irqsrc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tegra_gpio_pic_pre_ithread(device_t dev, struct intr_irqsrc *isrc)
{
	struct tegra_gpio_softc *sc;
	struct tegra_gpio_irqsrc *tgi;

	sc = device_get_softc(dev);
	tgi = (struct tegra_gpio_irqsrc *)isrc;

	tegra_gpio_isrc_mask(sc, tgi, 0);
	if (tegra_gpio_isrc_is_level(tgi))
		tegra_gpio_isrc_eoi(sc, tgi);
}