#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* lex_registers; int controller_index; scalar_t__ pci_revision; int /*<<< orphan*/ * scu_registers; int /*<<< orphan*/ * smu_registers; } ;
typedef  int /*<<< orphan*/  SMU_REGISTERS_T ;
typedef  int /*<<< orphan*/  SCU_REGISTERS_T ;
typedef  TYPE_1__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  ARLINGTON_LEX_BAR ; 
 int /*<<< orphan*/  ARLINGTON_SCU_BAR ; 
 int /*<<< orphan*/  ARLINGTON_SMU_BAR ; 
 int LEX_REGISTER_OFFSET ; 
 int /*<<< orphan*/  PATSBURG_IO_SPACE_BAR0 ; 
 int /*<<< orphan*/  PATSBURG_IO_SPACE_BAR1 ; 
 int /*<<< orphan*/  PATSBURG_SCU_BAR ; 
 int /*<<< orphan*/  PATSBURG_SMU_BAR ; 
 scalar_t__ SCU_PBG_HBA_REV_B0 ; 
 scalar_t__ scic_cb_pci_get_bar (TYPE_1__*,int /*<<< orphan*/ ) ; 

void scic_sds_pci_bar_initialization(
   SCIC_SDS_CONTROLLER_T* this_controller
)
{
#ifdef ARLINGTON_BUILD

   #define ARLINGTON_LEX_BAR  0
   #define ARLINGTON_SMU_BAR  1
   #define ARLINGTON_SCU_BAR  2
   #define LEX_REGISTER_OFFSET 0x40000

   this_controller->lex_registers =
      ((char *)scic_cb_pci_get_bar(
                     this_controller, ARLINGTON_LEX_BAR) + LEX_REGISTER_OFFSET);
   this_controller->smu_registers =
      (SMU_REGISTERS_T *)scic_cb_pci_get_bar(this_controller, ARLINGTON_SMU_BAR);
   this_controller->scu_registers =
      (SCU_REGISTERS_T *)scic_cb_pci_get_bar(this_controller, ARLINGTON_SCU_BAR);

#else // !ARLINGTON_BUILD

#if !defined(ENABLE_PCI_IO_SPACE_ACCESS)

   this_controller->smu_registers =
      (SMU_REGISTERS_T *)(
         (char *)scic_cb_pci_get_bar(this_controller, PATSBURG_SMU_BAR)
                +(0x4000 * this_controller->controller_index));
   this_controller->scu_registers =
      (SCU_REGISTERS_T *)(
         (char *)scic_cb_pci_get_bar(this_controller, PATSBURG_SCU_BAR)
                +(0x400000 * this_controller->controller_index));

#else // !defined(ENABLE_PCI_IO_SPACE_ACCESS)

   if (this_controller->controller_index == 0)
   {
      this_controller->smu_registers = (SMU_REGISTERS_T *)
         scic_cb_pci_get_bar(this_controller, PATSBURG_IO_SPACE_BAR0);
   }
   else
   {
      if (this_controller->pci_revision == SCU_PBG_HBA_REV_B0)
      {
         // SCU B0 violates PCI spec for size of IO bar this is corrected
         // in subsequent version of the hardware so we can safely use the
         // else condition below.
         this_controller->smu_registers = (SMU_REGISTERS_T *)
            (scic_cb_pci_get_bar(this_controller, PATSBURG_IO_SPACE_BAR0) + 0x100);
      }
      else
      {
         this_controller->smu_registers = (SMU_REGISTERS_T *)
            scic_cb_pci_get_bar(this_controller, PATSBURG_IO_SPACE_BAR1);
      }
   }

   // No need to get the bar.  We will be using the offset to write to
   // input/output ports via 0xA0 and 0xA4.
   this_controller->scu_registers = (SCU_REGISTERS_T *) 0;

#endif // !defined(ENABLE_PCI_IO_SPACE_ACCESS)

#endif // ARLINGTON_BUILD
}