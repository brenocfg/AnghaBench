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
typedef  enum mmc_bus_timing { ____Placeholder_mmc_bus_timing } mmc_bus_timing ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int HOST_TIMING_CAP (int,int) ; 
 int MMC_CAP_HSPEED ; 
 int MMC_CAP_MMC_DDR52 ; 
 int MMC_CAP_MMC_ENH_STROBE ; 
 int MMC_CAP_MMC_HS200 ; 
 int MMC_CAP_MMC_HS400 ; 
 int MMC_CAP_UHS_DDR50 ; 
 int MMC_CAP_UHS_SDR104 ; 
 int MMC_CAP_UHS_SDR12 ; 
 int MMC_CAP_UHS_SDR25 ; 
 int MMC_CAP_UHS_SDR50 ; 
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
 int mmcbr_get_caps (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
mmc_host_timing(device_t dev, enum mmc_bus_timing timing)
{
	int host_caps;

	host_caps = mmcbr_get_caps(dev);

#define	HOST_TIMING_CAP(host_caps, cap) ({				\
	bool retval;							\
	if (((host_caps) & (cap)) == (cap))				\
		retval = true;						\
	else								\
		retval = false;						\
	retval;								\
})

	switch (timing) {
	case bus_timing_normal:
		return (true);
	case bus_timing_hs:
		return (HOST_TIMING_CAP(host_caps, MMC_CAP_HSPEED));
	case bus_timing_uhs_sdr12:
		return (HOST_TIMING_CAP(host_caps, MMC_CAP_UHS_SDR12));
	case bus_timing_uhs_sdr25:
		return (HOST_TIMING_CAP(host_caps, MMC_CAP_UHS_SDR25));
	case bus_timing_uhs_ddr50:
		return (HOST_TIMING_CAP(host_caps, MMC_CAP_UHS_DDR50));
	case bus_timing_uhs_sdr50:
		return (HOST_TIMING_CAP(host_caps, MMC_CAP_UHS_SDR50));
	case bus_timing_uhs_sdr104:
		return (HOST_TIMING_CAP(host_caps, MMC_CAP_UHS_SDR104));
	case bus_timing_mmc_ddr52:
		return (HOST_TIMING_CAP(host_caps, MMC_CAP_MMC_DDR52));
	case bus_timing_mmc_hs200:
		return (HOST_TIMING_CAP(host_caps, MMC_CAP_MMC_HS200));
	case bus_timing_mmc_hs400:
		return (HOST_TIMING_CAP(host_caps, MMC_CAP_MMC_HS400));
	case bus_timing_mmc_hs400es:
		return (HOST_TIMING_CAP(host_caps, MMC_CAP_MMC_HS400 |
		    MMC_CAP_MMC_ENH_STROBE));
	}

#undef HOST_TIMING_CAP

	return (false);
}