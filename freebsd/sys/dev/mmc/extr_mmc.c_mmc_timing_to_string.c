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

/* Variables and functions */
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

__attribute__((used)) static const char *
mmc_timing_to_string(enum mmc_bus_timing timing)
{

	switch (timing) {
	case bus_timing_normal:
		return ("normal speed");
	case bus_timing_hs:
		return ("high speed");
	case bus_timing_uhs_sdr12:
	case bus_timing_uhs_sdr25:
	case bus_timing_uhs_sdr50:
	case bus_timing_uhs_sdr104:
		return ("single data rate");
	case bus_timing_uhs_ddr50:
	case bus_timing_mmc_ddr52:
		return ("dual data rate");
	case bus_timing_mmc_hs200:
		return ("HS200");
	case bus_timing_mmc_hs400:
		return ("HS400");
	case bus_timing_mmc_hs400es:
		return ("HS400 with enhanced strobe");
	}
	return ("");
}