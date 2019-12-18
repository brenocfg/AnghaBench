#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_16__ {int /*<<< orphan*/  identify_address_frame_buffer; } ;
struct TYPE_17__ {TYPE_1__ sas; } ;
struct TYPE_22__ {TYPE_2__ phy_type; } ;
struct TYPE_18__ {scalar_t__ smp_target; } ;
struct TYPE_19__ {TYPE_3__ bits; } ;
struct TYPE_20__ {TYPE_4__ u; } ;
struct TYPE_21__ {scalar_t__ address_frame_type; TYPE_5__ protocols; } ;
struct TYPE_15__ {int /*<<< orphan*/  uf_control; } ;
typedef  scalar_t__ SCI_STATUS ;
typedef  TYPE_6__ SCI_SAS_IDENTIFY_ADDRESS_FRAME_T ;
typedef  TYPE_7__ SCIC_SDS_PHY_T ;

/* Variables and functions */
 int SCIC_LOG_OBJECT_PHY ; 
 int SCIC_LOG_OBJECT_UNSOLICITED_FRAMES ; 
 int /*<<< orphan*/  SCIC_LOG_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_SDS_PHY_STARTING_SUBSTATE_AWAIT_SAS_POWER ; 
 int /*<<< orphan*/  SCIC_SDS_PHY_STARTING_SUBSTATE_FINAL ; 
 int /*<<< orphan*/  SCIC_SWAP_DWORD (int /*<<< orphan*/ ) ; 
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_6__*,int) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_7__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_controller_release_frame (TYPE_10__*,int /*<<< orphan*/ ) ; 
 TYPE_10__* scic_sds_phy_get_controller (TYPE_7__*) ; 
 int /*<<< orphan*/  scic_sds_phy_get_starting_substate_machine (TYPE_7__*) ; 
 scalar_t__ scic_sds_unsolicited_frame_control_get_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_phy_starting_substate_await_iaf_uf_frame_handler(
   SCIC_SDS_PHY_T *this_phy,
   U32            frame_index
)
{
   SCI_STATUS                        result;
   U32                              *frame_words;
   SCI_SAS_IDENTIFY_ADDRESS_FRAME_T *identify_frame;

   result = scic_sds_unsolicited_frame_control_get_header(
               &(scic_sds_phy_get_controller(this_phy)->uf_control),
               frame_index,
               (void **)&frame_words);

   if (result != SCI_SUCCESS)
   {
      return result;
   }

   frame_words[0] = SCIC_SWAP_DWORD(frame_words[0]);
   identify_frame = (SCI_SAS_IDENTIFY_ADDRESS_FRAME_T *)frame_words;

   if (identify_frame->address_frame_type == 0)
   {
      // Byte swap the rest of the frame so we can make
      // a copy of the buffer
      frame_words[1] = SCIC_SWAP_DWORD(frame_words[1]);
      frame_words[2] = SCIC_SWAP_DWORD(frame_words[2]);
      frame_words[3] = SCIC_SWAP_DWORD(frame_words[3]);
      frame_words[4] = SCIC_SWAP_DWORD(frame_words[4]);
      frame_words[5] = SCIC_SWAP_DWORD(frame_words[5]);

      memcpy(
         &this_phy->phy_type.sas.identify_address_frame_buffer,
         identify_frame,
         sizeof(SCI_SAS_IDENTIFY_ADDRESS_FRAME_T)
      );

      if (identify_frame->protocols.u.bits.smp_target)
      {
         // We got the IAF for an expander PHY go to the final state since
         // there are no power requirements for expander phys.
         sci_base_state_machine_change_state(
            scic_sds_phy_get_starting_substate_machine(this_phy),
            SCIC_SDS_PHY_STARTING_SUBSTATE_FINAL
         );
      }
      else
      {
         // We got the IAF we can now go to the await spinup semaphore state
         sci_base_state_machine_change_state(
            scic_sds_phy_get_starting_substate_machine(this_phy),
            SCIC_SDS_PHY_STARTING_SUBSTATE_AWAIT_SAS_POWER
         );
      }

      result = SCI_SUCCESS;
   }
   else
   {
      SCIC_LOG_WARNING((
         sci_base_object_get_logger(this_phy),
         SCIC_LOG_OBJECT_PHY | SCIC_LOG_OBJECT_UNSOLICITED_FRAMES,
         "PHY starting substate machine received unexpected frame id %x\n",
         frame_index
      ));
   }

   // Regardless of the result release this frame since we are done with it
   scic_sds_controller_release_frame(
      scic_sds_phy_get_controller(this_phy), frame_index
      );

   return result;
}