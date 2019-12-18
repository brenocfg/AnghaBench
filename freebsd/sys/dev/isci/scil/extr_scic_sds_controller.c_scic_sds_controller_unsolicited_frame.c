#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t U32 ;
struct TYPE_9__ {TYPE_1__* array; } ;
struct TYPE_10__ {TYPE_2__ buffers; } ;
struct TYPE_12__ {size_t remote_node_entries; int /*<<< orphan*/ ** device_table; int /*<<< orphan*/ * phy_table; TYPE_3__ uf_control; } ;
struct TYPE_11__ {scalar_t__ is_address_frame; } ;
struct TYPE_8__ {int /*<<< orphan*/  state; TYPE_4__* header; } ;
typedef  TYPE_4__ SCU_UNSOLICITED_FRAME_HEADER_T ;
typedef  scalar_t__ SCI_STATUS ;
typedef  int /*<<< orphan*/  SCIC_SDS_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_PHY_T ;
typedef  TYPE_5__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 size_t SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX ; 
 scalar_t__ SCI_FAILURE ; 
 scalar_t__ SCI_SUCCESS ; 
 size_t SCU_GET_COMPLETION_INDEX (size_t) ; 
 scalar_t__ SCU_GET_FRAME_ERROR (size_t) ; 
 size_t SCU_GET_FRAME_INDEX (size_t) ; 
 size_t SCU_GET_PROTOCOL_ENGINE_INDEX (size_t) ; 
 int /*<<< orphan*/  UNSOLICITED_FRAME_IN_USE ; 
 int /*<<< orphan*/  scic_sds_controller_release_frame (TYPE_5__*,size_t) ; 
 scalar_t__ scic_sds_phy_frame_handler (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ scic_sds_remote_device_frame_handler (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static
void scic_sds_controller_unsolicited_frame(
   SCIC_SDS_CONTROLLER_T *this_controller,
   U32                   completion_entry
)
{
   U32 index;
   U32 frame_index;

   SCU_UNSOLICITED_FRAME_HEADER_T * frame_header;
   SCIC_SDS_PHY_T                 * phy;
   SCIC_SDS_REMOTE_DEVICE_T       * device;

   SCI_STATUS result = SCI_FAILURE;

   frame_index = SCU_GET_FRAME_INDEX(completion_entry);

   frame_header
      = this_controller->uf_control.buffers.array[frame_index].header;
   this_controller->uf_control.buffers.array[frame_index].state
      = UNSOLICITED_FRAME_IN_USE;

   if (SCU_GET_FRAME_ERROR(completion_entry))
   {
      /// @todo If the IAF frame or SIGNATURE FIS frame has an error will
      ///       this cause a problem? We expect the phy initialization will
      ///       fail if there is an error in the frame.
      scic_sds_controller_release_frame(this_controller, frame_index);
      return;
   }

   if (frame_header->is_address_frame)
   {
      index = SCU_GET_PROTOCOL_ENGINE_INDEX(completion_entry);
      phy = &this_controller->phy_table[index];
      if (phy != NULL)
      {
         result = scic_sds_phy_frame_handler(phy, frame_index);
      }
   }
   else
   {

      index = SCU_GET_COMPLETION_INDEX(completion_entry);

      if (index == SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX)
      {
         // This is a signature fis or a frame from a direct attached SATA
         // device that has not yet been created.  In either case forwared
         // the frame to the PE and let it take care of the frame data.
         index = SCU_GET_PROTOCOL_ENGINE_INDEX(completion_entry);
         phy = &this_controller->phy_table[index];
         result = scic_sds_phy_frame_handler(phy, frame_index);
      }
      else
      {
         if (index < this_controller->remote_node_entries)
            device = this_controller->device_table[index];
         else
            device = NULL;

         if (device != NULL)
            result = scic_sds_remote_device_frame_handler(device, frame_index);
         else
            scic_sds_controller_release_frame(this_controller, frame_index);
      }
   }

   if (result != SCI_SUCCESS)
   {
      /// @todo Is there any reason to report some additional error message
      ///       when we get this failure notifiction?
   }
}