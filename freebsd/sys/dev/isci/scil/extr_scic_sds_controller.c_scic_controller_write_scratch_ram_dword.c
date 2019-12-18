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
 int scic_controller_get_scratch_ram_size (scalar_t__) ; 
 int /*<<< orphan*/  scu_controller_scratch_ram_register_write (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  scu_controller_scratch_ram_register_write_ext (int /*<<< orphan*/ *,int,int) ; 

SCI_STATUS scic_controller_write_scratch_ram_dword(
   SCI_CONTROLLER_HANDLE_T   controller,
   U32                       offset,
   U32                       value
)
{
   U32 zpt_index;

   if (offset < scic_controller_get_scratch_ram_size(controller))
   {
      SCIC_SDS_CONTROLLER_T * scic_controller = (SCIC_SDS_CONTROLLER_T *)controller;

      if(offset <= SCU_MAX_ZPT_DWORD_INDEX)
      {
         zpt_index = offset + (offset - (offset % 4)) + 4;

         scu_controller_scratch_ram_register_write(scic_controller,zpt_index,value);
      }
      else //offset > SCU_MAX_ZPT_DWORD_INDEX
      {
         offset = offset - 132;

         zpt_index = offset + (offset - (offset % 4)) + 4;

         scu_controller_scratch_ram_register_write_ext(scic_controller,zpt_index,value);

      }

      return SCI_SUCCESS;
   }
   else
   {
      return SCI_FAILURE_INVALID_PARAMETER_VALUE;
   }
}