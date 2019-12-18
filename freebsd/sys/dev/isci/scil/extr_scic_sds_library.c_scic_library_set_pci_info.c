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
struct TYPE_5__ {scalar_t__ pci_revision; int /*<<< orphan*/  pci_device; } ;
struct TYPE_4__ {scalar_t__ revision; int /*<<< orphan*/  device_id; } ;
typedef  TYPE_1__ SCI_PCI_COMMON_HEADER_T ;
typedef  scalar_t__ SCI_LIBRARY_HANDLE_T ;
typedef  TYPE_2__ SCIC_SDS_LIBRARY_T ;

/* Variables and functions */
 scalar_t__ SCIC_SDS_PCI_REVISION_A0 ; 
 void* SCIC_SDS_PCI_REVISION_A2 ; 
 scalar_t__ SCIC_SDS_PCI_REVISION_B0 ; 

void scic_library_set_pci_info(
   SCI_LIBRARY_HANDLE_T      library,
   SCI_PCI_COMMON_HEADER_T * pci_header
)
{
   SCIC_SDS_LIBRARY_T *this_library;
   this_library = (SCIC_SDS_LIBRARY_T *)library;

   this_library->pci_device   = pci_header->device_id;

#if defined(PBG_HBA_A0_BUILD)
   this_library->pci_revision = SCIC_SDS_PCI_REVISION_A0;
#elif defined(PBG_HBA_A2_BUILD)
   this_library->pci_revision = SCIC_SDS_PCI_REVISION_A2;
#elif defined(PBG_HBA_BETA_BUILD)
   this_library->pci_revision = SCIC_SDS_PCI_REVISION_B0;
#elif defined(PBG_BUILD)
   // The SCU PCI function revision ID for A0/A2 is not populated
   // properly.  As a result, we force the revision ID to A2 for
   // this situation.  Therefore, the standard PBG build will not
   // work for A0.
   if (pci_header->revision == SCIC_SDS_PCI_REVISION_A0)
      this_library->pci_revision = SCIC_SDS_PCI_REVISION_A2;
   else
      this_library->pci_revision = pci_header->revision;
#endif
}