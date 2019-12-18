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
struct tegra_sku_info {scalar_t__ soc_speedo_value; scalar_t__ cpu_speedo_value; scalar_t__ gpu_speedo_value; int soc_process_id; int cpu_process_id; int gpu_process_id; void* gpu_iddq_value; void* cpu_iddq_value; void* soc_iddq_value; void* sku_id; } ;
struct tegra_efuse_softc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 void* RD4 (struct tegra_efuse_softc*,int /*<<< orphan*/ ) ; 
 int TEGRA124_CPU_PROCESS_CORNERS ; 
 int /*<<< orphan*/  TEGRA124_FUSE_CPU_IDDQ ; 
 int /*<<< orphan*/  TEGRA124_FUSE_CPU_SPEEDO_0 ; 
 int /*<<< orphan*/  TEGRA124_FUSE_CPU_SPEEDO_2 ; 
 int /*<<< orphan*/  TEGRA124_FUSE_GPU_IDDQ ; 
 int /*<<< orphan*/  TEGRA124_FUSE_SKU_INFO ; 
 int /*<<< orphan*/  TEGRA124_FUSE_SOC_IDDQ ; 
 int /*<<< orphan*/  TEGRA124_FUSE_SOC_SPEEDO_0 ; 
 int TEGRA124_GPU_PROCESS_CORNERS ; 
 int TEGRA124_SOC_PROCESS_CORNERS ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__** tegra124_cpu_process_speedos ; 
 scalar_t__** tegra124_gpu_process_speedos ; 
 int /*<<< orphan*/  tegra124_rev_sku_to_speedo_ids (struct tegra_efuse_softc*,struct tegra_sku_info*,int*) ; 
 scalar_t__** tegra124_soc_process_speedos ; 

__attribute__((used)) static void
tegra124_init_speedo(struct tegra_efuse_softc *sc, struct tegra_sku_info *sku)
{
	int i, threshold;

	sku->sku_id = RD4(sc, TEGRA124_FUSE_SKU_INFO);
	sku->soc_iddq_value = RD4(sc, TEGRA124_FUSE_SOC_IDDQ);
	sku->cpu_iddq_value = RD4(sc, TEGRA124_FUSE_CPU_IDDQ);
	sku->gpu_iddq_value = RD4(sc, TEGRA124_FUSE_GPU_IDDQ);
	sku->soc_speedo_value = RD4(sc, TEGRA124_FUSE_SOC_SPEEDO_0);
	sku->cpu_speedo_value = RD4(sc, TEGRA124_FUSE_CPU_SPEEDO_0);
	sku->gpu_speedo_value = RD4(sc, TEGRA124_FUSE_CPU_SPEEDO_2);

	if (sku->cpu_speedo_value == 0) {
		device_printf(sc->dev, "CPU Speedo value is not fused.\n");
		return;
	}

	tegra124_rev_sku_to_speedo_ids(sc, sku, &threshold);

	for (i = 0; i < TEGRA124_SOC_PROCESS_CORNERS; i++) {
		if (sku->soc_speedo_value <
			tegra124_soc_process_speedos[threshold][i])
			break;
	}
	sku->soc_process_id = i;

	for (i = 0; i < TEGRA124_CPU_PROCESS_CORNERS; i++) {
		if (sku->cpu_speedo_value <
			tegra124_cpu_process_speedos[threshold][i])
				break;
	}
	sku->cpu_process_id = i;

	for (i = 0; i < TEGRA124_GPU_PROCESS_CORNERS; i++) {
		if (sku->gpu_speedo_value <
			tegra124_gpu_process_speedos[threshold][i])
			break;
	}
	sku->gpu_process_id = i;

}