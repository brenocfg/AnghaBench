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
struct resource {int dummy; } ;
struct intr_map_data {scalar_t__ type; } ;
struct intr_irqsrc {scalar_t__ isrc_handlers; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOTSUP ; 
 scalar_t__ INTR_MAP_DATA_MSI ; 
 struct tegra_pcib_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_pcib_msi_enable_intr (int /*<<< orphan*/ ,struct intr_irqsrc*) ; 

__attribute__((used)) static int
tegra_pcib_msi_setup_intr(device_t dev, struct intr_irqsrc *isrc,
    struct resource *res, struct intr_map_data *data)
{
	struct tegra_pcib_softc *sc;
	struct tegra_pcib_irqsrc *tgi;

	sc = device_get_softc(dev);
	tgi = (struct tegra_pcib_irqsrc *)isrc;

	if (data == NULL || data->type != INTR_MAP_DATA_MSI)
		return (ENOTSUP);

	if (isrc->isrc_handlers == 0)
		tegra_pcib_msi_enable_intr(dev, isrc);

	return (0);
}