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
#define  AR9300_DEVID_AR1111_PCIE 137 
#define  AR9300_DEVID_AR9330 136 
#define  AR9300_DEVID_AR9340 135 
#define  AR9300_DEVID_AR9380_PCIE 134 
#define  AR9300_DEVID_AR946X_PCIE 133 
#define  AR9300_DEVID_AR9485_PCIE 132 
#define  AR9300_DEVID_AR9580_PCIE 131 
#define  AR9300_DEVID_QCA953X 130 
#define  AR9300_DEVID_QCA955X 129 
#define  AR9300_DEVID_QCA9565 128 
 scalar_t__ ATHEROS_VENDOR_ID ; 

__attribute__((used)) static const char*
ar9300_probe(uint16_t vendorid, uint16_t devid)
{
    if (vendorid != ATHEROS_VENDOR_ID)
        return AH_NULL;

    switch (devid) {
    case AR9300_DEVID_AR9380_PCIE: /* PCIE (Osprey) */
        return "Atheros AR938x";
    case AR9300_DEVID_AR9340: /* Wasp */
        return "Atheros AR934x";
    case AR9300_DEVID_AR9485_PCIE: /* Poseidon */
        return "Atheros AR9485";
    case AR9300_DEVID_AR9580_PCIE: /* Peacock */
        return "Atheros AR9580";
    case AR9300_DEVID_AR946X_PCIE: /* AR9462, AR9463, AR9482 */
        return "Atheros AR946x/AR948x";
    case AR9300_DEVID_AR9330: /* Hornet */
        return "Atheros AR933x";
    case AR9300_DEVID_QCA955X: /* Scorpion */
        return "Qualcomm Atheros QCA955x";
    case AR9300_DEVID_QCA9565: /* Aphrodite */
         return "Qualcomm Atheros AR9565";
    case AR9300_DEVID_QCA953X: /* Honeybee */
         return "Qualcomm Atheros QCA953x";
    case AR9300_DEVID_AR1111_PCIE:
         return "Atheros AR1111";
    default:
        return AH_NULL;
    }

    return AH_NULL;
}