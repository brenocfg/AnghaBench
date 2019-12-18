#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct agtiapi_softc {int /*<<< orphan*/  my_dev; TYPE_1__* pCardInfo; } ;
typedef  int /*<<< orphan*/  U32_64 ;
struct TYPE_4__ {int /*<<< orphan*/  busNum; int /*<<< orphan*/  pciIOAddrUp; int /*<<< orphan*/  pciIOAddrLow; int /*<<< orphan*/  pciMemBase; int /*<<< orphan*/  deviceNum; int /*<<< orphan*/  pciMemBaseSpc; int /*<<< orphan*/  vendorId; int /*<<< orphan*/  deviceId; } ;
struct TYPE_3__ {int /*<<< orphan*/  pciIOAddrUp; int /*<<< orphan*/  pciIOAddrLow; int /*<<< orphan*/  pciMemBase; int /*<<< orphan*/  pciMemBaseSpc; } ;
typedef  TYPE_2__ CardInfo_t ;

/* Variables and functions */
 int PCI_NUMBER_BARS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_get_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_slot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_vendor (int /*<<< orphan*/ ) ; 

int agtiapi_getCardInfo ( struct agtiapi_softc *pCard,
                          U32_64                size,
                          void                 *buffer )
{
  CardInfo_t       *pCardInfo;

  pCardInfo = (CardInfo_t *)buffer;

  pCardInfo->deviceId = pci_get_device(pCard->my_dev);
  pCardInfo->vendorId =pci_get_vendor(pCard->my_dev) ;
  memcpy( pCardInfo->pciMemBaseSpc,
          pCard->pCardInfo->pciMemBaseSpc,
          ((sizeof(U32_64))*PCI_NUMBER_BARS) );
  pCardInfo->deviceNum = pci_get_slot(pCard->my_dev);
  pCardInfo->pciMemBase = pCard->pCardInfo->pciMemBase;
  pCardInfo->pciIOAddrLow = pCard->pCardInfo->pciIOAddrLow;
  pCardInfo->pciIOAddrUp = pCard->pCardInfo->pciIOAddrUp;
  pCardInfo->busNum =pci_get_bus(pCard->my_dev);
  return 0;
}