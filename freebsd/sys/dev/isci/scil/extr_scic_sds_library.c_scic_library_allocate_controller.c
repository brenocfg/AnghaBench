#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int pci_device; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  scalar_t__ SCI_LIBRARY_HANDLE_T ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;
typedef  TYPE_1__ SCIC_SDS_LIBRARY_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_BASE_LIBRARY_ALLOCATE_CONTROLLER (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCI_FAILURE_UNSUPPORTED_PCI_DEVICE_ID ; 

SCI_STATUS scic_library_allocate_controller(
   SCI_LIBRARY_HANDLE_T    library,
   SCI_CONTROLLER_HANDLE_T *new_controller
)
{
   SCI_STATUS status;
   SCIC_SDS_LIBRARY_T *this_library;

   this_library = (SCIC_SDS_LIBRARY_T *)library;

   if (
         (  (this_library->pci_device >= 0x1D60)
         && (this_library->pci_device <= 0x1D62)
         )
      || (  (this_library->pci_device >= 0x1D64)
         && (this_library->pci_device <= 0x1D65)
         )
      || (  (this_library->pci_device >= 0x1D68)
         && (this_library->pci_device <= 0x1D6F)
         )
      )
   {
      SCI_BASE_LIBRARY_ALLOCATE_CONTROLLER(
         this_library, new_controller, &status);
   }
   else
      status = SCI_FAILURE_UNSUPPORTED_PCI_DEVICE_ID;

   return status;
}