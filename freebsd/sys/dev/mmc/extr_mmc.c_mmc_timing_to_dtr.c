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
typedef  int /*<<< orphan*/  uint32_t ;
struct mmc_ivars {int /*<<< orphan*/  hs_tran_speed; int /*<<< orphan*/  tran_speed; } ;
typedef  enum mmc_bus_timing { ____Placeholder_mmc_bus_timing } mmc_bus_timing ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_TYPE_DDR52_MAX ; 
 int /*<<< orphan*/  MMC_TYPE_HS200_HS400ES_MAX ; 
 int /*<<< orphan*/  SD_DDR50_MAX ; 
 int /*<<< orphan*/  SD_SDR104_MAX ; 
 int /*<<< orphan*/  SD_SDR12_MAX ; 
 int /*<<< orphan*/  SD_SDR25_MAX ; 
 int /*<<< orphan*/  SD_SDR50_MAX ; 
#define  bus_timing_hs 138 
#define  bus_timing_mmc_ddr52 137 
#define  bus_timing_mmc_hs200 136 
#define  bus_timing_mmc_hs400 135 
#define  bus_timing_mmc_hs400es 134 
#define  bus_timing_normal 133 
#define  bus_timing_uhs_ddr50 132 
#define  bus_timing_uhs_sdr104 131 
#define  bus_timing_uhs_sdr12 130 
#define  bus_timing_uhs_sdr25 129 
#define  bus_timing_uhs_sdr50 128 

__attribute__((used)) static uint32_t
mmc_timing_to_dtr(struct mmc_ivars *ivar, enum mmc_bus_timing timing)
{

	switch (timing) {
	case bus_timing_normal:
		return (ivar->tran_speed);
	case bus_timing_hs:
		return (ivar->hs_tran_speed);
	case bus_timing_uhs_sdr12:
		return (SD_SDR12_MAX);
	case bus_timing_uhs_sdr25:
		return (SD_SDR25_MAX);
	case bus_timing_uhs_ddr50:
		return (SD_DDR50_MAX);
	case bus_timing_uhs_sdr50:
		return (SD_SDR50_MAX);
	case bus_timing_uhs_sdr104:
		return (SD_SDR104_MAX);
	case bus_timing_mmc_ddr52:
		return (MMC_TYPE_DDR52_MAX);
	case bus_timing_mmc_hs200:
	case bus_timing_mmc_hs400:
	case bus_timing_mmc_hs400es:
		return (MMC_TYPE_HS200_HS400ES_MAX);
	}
	return (0);
}