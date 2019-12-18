#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* br_control; void* br_pribus; void* br_secbus; void* br_subbus; void* br_seclat; } ;
struct TYPE_5__ {int hdrtype; int /*<<< orphan*/  nummaps; void* subdevice; void* subvendor; TYPE_1__ bridge; void* maxlat; void* mingnt; } ;
typedef  TYPE_2__ pcicfgregs ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCIM_HDRTYPE ; 
#define  PCIM_HDRTYPE_BRIDGE 130 
#define  PCIM_HDRTYPE_CARDBUS 129 
#define  PCIM_HDRTYPE_NORMAL 128 
 int /*<<< orphan*/  PCIR_BRIDGECTL_1 ; 
 int /*<<< orphan*/  PCIR_BRIDGECTL_2 ; 
 int /*<<< orphan*/  PCIR_MAXLAT ; 
 int /*<<< orphan*/  PCIR_MINGNT ; 
 int /*<<< orphan*/  PCIR_PRIBUS_1 ; 
 int /*<<< orphan*/  PCIR_PRIBUS_2 ; 
 int /*<<< orphan*/  PCIR_SECBUS_1 ; 
 int /*<<< orphan*/  PCIR_SECBUS_2 ; 
 int /*<<< orphan*/  PCIR_SECLAT_1 ; 
 int /*<<< orphan*/  PCIR_SECLAT_2 ; 
 int /*<<< orphan*/  PCIR_SUBBUS_1 ; 
 int /*<<< orphan*/  PCIR_SUBBUS_2 ; 
 int /*<<< orphan*/  PCIR_SUBDEV_0 ; 
 int /*<<< orphan*/  PCIR_SUBDEV_2 ; 
 int /*<<< orphan*/  PCIR_SUBVEND_0 ; 
 int /*<<< orphan*/  PCIR_SUBVEND_2 ; 
 int /*<<< orphan*/  PCI_MAXMAPS_0 ; 
 int /*<<< orphan*/  PCI_MAXMAPS_1 ; 
 int /*<<< orphan*/  PCI_MAXMAPS_2 ; 
 void* REG (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
pci_hdrtypedata(device_t pcib, int b, int s, int f, pcicfgregs *cfg)
{
#define	REG(n, w)	PCIB_READ_CONFIG(pcib, b, s, f, n, w)
	switch (cfg->hdrtype & PCIM_HDRTYPE) {
	case PCIM_HDRTYPE_NORMAL:
		cfg->subvendor      = REG(PCIR_SUBVEND_0, 2);
		cfg->subdevice      = REG(PCIR_SUBDEV_0, 2);
		cfg->mingnt         = REG(PCIR_MINGNT, 1);
		cfg->maxlat         = REG(PCIR_MAXLAT, 1);
		cfg->nummaps	    = PCI_MAXMAPS_0;
		break;
	case PCIM_HDRTYPE_BRIDGE:
		cfg->bridge.br_seclat = REG(PCIR_SECLAT_1, 1);
		cfg->bridge.br_subbus = REG(PCIR_SUBBUS_1, 1);
		cfg->bridge.br_secbus = REG(PCIR_SECBUS_1, 1);
		cfg->bridge.br_pribus = REG(PCIR_PRIBUS_1, 1);
		cfg->bridge.br_control = REG(PCIR_BRIDGECTL_1, 2);
		cfg->nummaps	    = PCI_MAXMAPS_1;
		break;
	case PCIM_HDRTYPE_CARDBUS:
		cfg->bridge.br_seclat = REG(PCIR_SECLAT_2, 1);
		cfg->bridge.br_subbus = REG(PCIR_SUBBUS_2, 1);
		cfg->bridge.br_secbus = REG(PCIR_SECBUS_2, 1);
		cfg->bridge.br_pribus = REG(PCIR_PRIBUS_2, 1);
		cfg->bridge.br_control = REG(PCIR_BRIDGECTL_2, 2);
		cfg->subvendor      = REG(PCIR_SUBVEND_2, 2);
		cfg->subdevice      = REG(PCIR_SUBDEV_2, 2);
		cfg->nummaps	    = PCI_MAXMAPS_2;
		break;
	}
#undef REG
}