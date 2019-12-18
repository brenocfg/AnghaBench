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
struct tegra_sku_info {int cpu_speedo_id; int soc_speedo_id; int gpu_speedo_id; int sku_id; } ;
struct tegra_efuse_softc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int TEGRA124_THRESHOLD_INDEX_0 ; 
 int TEGRA124_THRESHOLD_INDEX_1 ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
tegra124_rev_sku_to_speedo_ids(struct tegra_efuse_softc *sc,
    struct tegra_sku_info *sku, int *threshold)
{

	/* Assign to default */
	sku->cpu_speedo_id = 0;
	sku->soc_speedo_id = 0;
	sku->gpu_speedo_id = 0;
	*threshold = TEGRA124_THRESHOLD_INDEX_0;

	switch (sku->sku_id) {
	case 0x00: /* Eng sku */
	case 0x0F:
	case 0x23:
		/* Using the default */
		break;
	case 0x83:
		sku->cpu_speedo_id = 2;
		break;

	case 0x1F:
	case 0x87:
	case 0x27:
		sku->cpu_speedo_id = 2;
		sku->soc_speedo_id = 0;
		sku->gpu_speedo_id = 1;
		*threshold = TEGRA124_THRESHOLD_INDEX_0;
		break;
	case 0x81:
	case 0x21:
	case 0x07:
		sku->cpu_speedo_id = 1;
		sku->soc_speedo_id = 1;
		sku->gpu_speedo_id = 1;
		*threshold = TEGRA124_THRESHOLD_INDEX_1;
		break;
	case 0x49:
	case 0x4A:
	case 0x48:
		sku->cpu_speedo_id = 4;
		sku->soc_speedo_id = 2;
		sku->gpu_speedo_id = 3;
		*threshold = TEGRA124_THRESHOLD_INDEX_1;
		break;
	default:
		device_printf(sc->dev, " Unknown SKU ID %d\n", sku->sku_id);
		break;
	}
}