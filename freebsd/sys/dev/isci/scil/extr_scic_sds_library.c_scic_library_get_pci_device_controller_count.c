#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int U8 ;
typedef  int U16 ;
struct TYPE_2__ {int pci_device; scalar_t__ pci_revision; } ;
typedef  scalar_t__ SCI_LIBRARY_HANDLE_T ;
typedef  TYPE_1__ SCIC_SDS_LIBRARY_T ;

/* Variables and functions */
 scalar_t__ SCU_PBG_HBA_REV_B0 ; 
 scalar_t__ SCU_PBG_HBA_REV_C0 ; 
 scalar_t__ SCU_PBG_HBA_REV_C1 ; 

U8 scic_library_get_pci_device_controller_count(
   SCI_LIBRARY_HANDLE_T library
)
{
   SCIC_SDS_LIBRARY_T *this_library;
   U16 device_id;

   this_library = (SCIC_SDS_LIBRARY_T *)library;
   device_id = this_library->pci_device;

   //Check if we are on a b0 or c0 which has 2 controllers
   if (
         // Warning: If 0x1d66 is ever defined to be a single controller
         //          this logic will fail.
         //          If 0x1d63 or 0x1d67 is ever defined to be dual
         //          controller this logic will fail.
         ((device_id & 0xFFF1) == 0x1D60)
      && (
            (this_library->pci_revision == SCU_PBG_HBA_REV_B0)
         || (this_library->pci_revision == SCU_PBG_HBA_REV_C0)
         || (this_library->pci_revision == SCU_PBG_HBA_REV_C1)
         )
      )
      return 2;
   else
      return 1;
}