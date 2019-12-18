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
#define  AR5212_AR2413 135 
#define  AR5212_AR2417 134 
#define  AR5212_AR5413 133 
#define  AR5212_AR5424 132 
#define  AR5212_DEFAULT 131 
#define  AR5212_DEVID 130 
#define  AR5212_DEVID_IBM 129 
#define  AR5212_FPGA 128 
 scalar_t__ ATHEROS_3COM2_VENDOR_ID ; 
 scalar_t__ ATHEROS_3COM_VENDOR_ID ; 
 scalar_t__ ATHEROS_VENDOR_ID ; 

__attribute__((used)) static const char*
ar5212Probe(uint16_t vendorid, uint16_t devid)
{
	if (vendorid == ATHEROS_VENDOR_ID ||
	    vendorid == ATHEROS_3COM_VENDOR_ID ||
	    vendorid == ATHEROS_3COM2_VENDOR_ID) {
		switch (devid) {
		case AR5212_FPGA:
			return "Atheros 5212 (FPGA)";
		case AR5212_DEVID:
		case AR5212_DEVID_IBM:
		case AR5212_DEFAULT:
			return "Atheros 5212";
		case AR5212_AR2413:
			return "Atheros 2413";
		case AR5212_AR2417:
			return "Atheros 2417";
		case AR5212_AR5413:
			return "Atheros 5413";
		case AR5212_AR5424:
			return "Atheros 5424/2424";
		}
	}
	return AH_NULL;
}