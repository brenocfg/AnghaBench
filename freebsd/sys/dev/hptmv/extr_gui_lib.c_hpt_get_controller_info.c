#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; } ;
struct TYPE_5__ {int ChipFlags; int NumBuses; int /*<<< orphan*/  szProductID; int /*<<< orphan*/  szVendorID; scalar_t__ ChipType; scalar_t__ InterruptLevel; } ;
typedef  TYPE_1__* PCONTROLLER_INFO ;
typedef  TYPE_2__ IAL_ADAPTER_T ;

/* Variables and functions */
 int CHIP_SUPPORT_ULTRA_100 ; 
 int CHIP_SUPPORT_ULTRA_133 ; 
 int CHIP_SUPPORT_ULTRA_150 ; 
 char* GUI_CONTROLLER_NAME ; 
 int /*<<< orphan*/  _set_product_id (char*) ; 
 TYPE_2__* gIal_Adapter ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

int hpt_get_controller_info(int id, PCONTROLLER_INFO pInfo)
{
	IAL_ADAPTER_T    *pAdapTemp;
	int iControllerCount = 0;

	for (pAdapTemp = gIal_Adapter; pAdapTemp; pAdapTemp = pAdapTemp->next) {
		if (iControllerCount++==id) {
			pInfo->InterruptLevel = 0;
			pInfo->ChipType = 0;
			pInfo->ChipFlags = CHIP_SUPPORT_ULTRA_100;
			strcpy( pInfo->szVendorID, "HighPoint Technologies, Inc.");
#ifdef GUI_CONTROLLER_NAME
#ifdef FORCE_ATA150_DISPLAY
			/* show "Bus Type: ATA/150" in GUI for SATA controllers */
			pInfo->ChipFlags = CHIP_SUPPORT_ULTRA_150;
#endif
			strcpy(pInfo->szProductID, GUI_CONTROLLER_NAME);
#define _set_product_id(x)
#else 
#define _set_product_id(x) strcpy(pInfo->szProductID, x)
#endif
			_set_product_id("RocketRAID 18xx SATA Controller");			
			pInfo->NumBuses = 8;
			pInfo->ChipFlags |= CHIP_SUPPORT_ULTRA_133|CHIP_SUPPORT_ULTRA_150;
			return 0;
		}
	}
	return -1;
}