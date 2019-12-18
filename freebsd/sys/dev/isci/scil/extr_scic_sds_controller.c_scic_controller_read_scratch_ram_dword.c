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
typedef  int U32 ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  scalar_t__ SCI_CONTROLLER_HANDLE_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_FAILURE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int SCU_MAX_ZPT_DWORD_INDEX ; 
 int SCU_RAM_INIT_COMPLETED ; 
 int SMU_SMUCSR_READ (int /*<<< orphan*/ *) ; 
 int scic_controller_get_scratch_ram_size (scalar_t__) ; 
 int scu_controller_scratch_ram_register_read (int /*<<< orphan*/ *,int) ; 
 int scu_controller_scratch_ram_register_read_ext (int /*<<< orphan*/ *,int) ; 

SCI_STATUS scic_controller_read_scratch_ram_dword(
   SCI_CONTROLLER_HANDLE_T   controller,
   U32                       offset,
   U32                     * value
)
{
   U32 zpt_index;
   SCIC_SDS_CONTROLLER_T * scic_controller = (SCIC_SDS_CONTROLLER_T *)controller;
   U32 status = SMU_SMUCSR_READ(scic_controller);

   //Check if the SCU Scratch RAM been initialized, if not return zeros
   if ((status & SCU_RAM_INIT_COMPLETED) != SCU_RAM_INIT_COMPLETED)
   {
      *value = 0x00000000;
      return SCI_SUCCESS;
   }

   if (offset < scic_controller_get_scratch_ram_size(controller))
   {
      if(offset <= SCU_MAX_ZPT_DWORD_INDEX)
      {
         zpt_index = offset + (offset - (offset % 4)) + 4;

         *value = scu_controller_scratch_ram_register_read(scic_controller,zpt_index);
      }
      else //offset > SCU_MAX_ZPT_DWORD_INDEX
      {
         offset = offset - 132;

         zpt_index = offset + (offset - (offset % 4)) + 4;

         *value = scu_controller_scratch_ram_register_read_ext(scic_controller,zpt_index);
      }

      return SCI_SUCCESS;
   }
   else
   {
      return SCI_FAILURE_INVALID_PARAMETER_VALUE;
   }
}