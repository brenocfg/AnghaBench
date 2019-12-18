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
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 char const* AH_NULL ; 
#define  AR5212_AR2313_REV8 136 
#define  AR5212_AR2315_REV6 135 
#define  AR5212_AR2315_REV7 134 
#define  AR5212_AR2317_REV1 133 
#define  AR5212_AR2317_REV2 132 
#define  AR5212_AR2413 131 
#define  AR5212_AR2417 130 
#define  AR5212_AR5312_REV2 129 
#define  AR5212_AR5312_REV7 128 
 scalar_t__ ATHEROS_VENDOR_ID ; 

__attribute__((used)) static const char*
ar5312Probe(uint16_t vendorid, uint16_t devid)
{
	if (vendorid == ATHEROS_VENDOR_ID) {
		switch (devid) {
		case AR5212_AR5312_REV2:
		case AR5212_AR5312_REV7:
			return "Atheros 5312 WiSoC";
		case AR5212_AR2313_REV8:
			return "Atheros 2313 WiSoC";
		case AR5212_AR2315_REV6:
		case AR5212_AR2315_REV7:
			return "Atheros 2315 WiSoC";
		case AR5212_AR2317_REV1:
		case AR5212_AR2317_REV2:
			return "Atheros 2317 WiSoC";
		case AR5212_AR2413:
			return "Atheros 2413";
		case AR5212_AR2417:
			return "Atheros 2417";
		}
	}
	return AH_NULL;
}