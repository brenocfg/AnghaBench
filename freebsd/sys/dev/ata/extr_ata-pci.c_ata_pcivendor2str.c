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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  ATA_ACARD_ID 150 
#define  ATA_ACER_LABS_ID 149 
#define  ATA_ADAPTEC_ID 148 
#define  ATA_AMD_ID 147 
#define  ATA_ATI_ID 146 
#define  ATA_CENATEK_ID 145 
#define  ATA_CYPRESS_ID 144 
#define  ATA_CYRIX_ID 143 
#define  ATA_HIGHPOINT_ID 142 
#define  ATA_INTEL_ID 141 
#define  ATA_ITE_ID 140 
#define  ATA_JMICRON_ID 139 
#define  ATA_MARVELL2_ID 138 
#define  ATA_MARVELL_ID 137 
#define  ATA_MICRON_ID 136 
#define  ATA_NATIONAL_ID 135 
#define  ATA_NETCELL_ID 134 
#define  ATA_NVIDIA_ID 133 
#define  ATA_PROMISE_ID 132 
#define  ATA_SERVERWORKS_ID 131 
#define  ATA_SILICON_IMAGE_ID 130 
#define  ATA_SIS_ID 129 
#define  ATA_VIA_ID 128 
 int pci_get_vendor (int /*<<< orphan*/ ) ; 

const char *
ata_pcivendor2str(device_t dev)
{
    switch (pci_get_vendor(dev)) {
    case ATA_ACARD_ID:          return "Acard";
    case ATA_ACER_LABS_ID:      return "AcerLabs";
    case ATA_AMD_ID:            return "AMD";
    case ATA_ADAPTEC_ID:        return "Adaptec";
    case ATA_ATI_ID:            return "ATI";
    case ATA_CYRIX_ID:          return "Cyrix";
    case ATA_CYPRESS_ID:        return "Cypress";
    case ATA_HIGHPOINT_ID:      return "HighPoint";
    case ATA_INTEL_ID:          return "Intel";
    case ATA_ITE_ID:            return "ITE";
    case ATA_JMICRON_ID:        return "JMicron";
    case ATA_MARVELL_ID:        return "Marvell";
    case ATA_MARVELL2_ID:       return "Marvell";
    case ATA_NATIONAL_ID:       return "National";
    case ATA_NETCELL_ID:        return "Netcell";
    case ATA_NVIDIA_ID:         return "nVidia";
    case ATA_PROMISE_ID:        return "Promise";
    case ATA_SERVERWORKS_ID:    return "ServerWorks";
    case ATA_SILICON_IMAGE_ID:  return "SiI";
    case ATA_SIS_ID:            return "SiS";
    case ATA_VIA_ID:            return "VIA";
    case ATA_CENATEK_ID:        return "Cenatek";
    case ATA_MICRON_ID:         return "Micron";
    default:                    return "Generic";
    }
}