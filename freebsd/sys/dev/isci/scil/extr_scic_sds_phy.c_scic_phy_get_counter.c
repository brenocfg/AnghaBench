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
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_4__ {int /*<<< orphan*/ * error_counter; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  scalar_t__ SCI_PHY_HANDLE_T ;
typedef  TYPE_1__ SCIC_SDS_PHY_T ;
typedef  int /*<<< orphan*/  SCIC_PHY_COUNTER_ID_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_OBJECT_PHY ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
#define  SCIC_PHY_COUNTER_INACTIVITY_TIMER_EXPIRED 144 
#define  SCIC_PHY_COUNTER_LOSS_OF_SYNC_ERROR 143 
#define  SCIC_PHY_COUNTER_RECEIVED_CREDIT_BLOCKED 142 
#define  SCIC_PHY_COUNTER_RECEIVED_DISPARITY_ERROR 141 
#define  SCIC_PHY_COUNTER_RECEIVED_DONE_ACK_NAK_TIMEOUT 140 
#define  SCIC_PHY_COUNTER_RECEIVED_DONE_CREDIT_TIMEOUT 139 
#define  SCIC_PHY_COUNTER_RECEIVED_FRAME 138 
#define  SCIC_PHY_COUNTER_RECEIVED_FRAME_AFTER_DONE 137 
#define  SCIC_PHY_COUNTER_RECEIVED_FRAME_CRC_ERROR 136 
#define  SCIC_PHY_COUNTER_RECEIVED_FRAME_DWORD 135 
#define  SCIC_PHY_COUNTER_RECEIVED_FRAME_WITHOUT_CREDIT 134 
#define  SCIC_PHY_COUNTER_RECEIVED_SHORT_FRAME 133 
#define  SCIC_PHY_COUNTER_SN_DWORD_SYNC_ERROR 132 
#define  SCIC_PHY_COUNTER_TRANSMITTED_DONE_ACK_NAK_TIMEOUT 131 
#define  SCIC_PHY_COUNTER_TRANSMITTED_DONE_CREDIT_TIMEOUT 130 
#define  SCIC_PHY_COUNTER_TRANSMITTED_FRAME 129 
#define  SCIC_PHY_COUNTER_TRANSMITTED_FRAME_DWORD 128 
 int /*<<< orphan*/  SCI_FAILURE ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 size_t SCU_ERR_CNT_INACTIVITY_TIMER_EXPIRED_INDEX ; 
 size_t SCU_ERR_CNT_RX_CREDIT_BLOCKED_RECEIVED_INDEX ; 
 size_t SCU_ERR_CNT_RX_DONE_ACK_NAK_TIMEOUT_INDEX ; 
 size_t SCU_ERR_CNT_RX_DONE_CREDIT_TIMEOUT_INDEX ; 
 size_t SCU_ERR_CNT_TX_DONE_ACK_NAK_TIMEOUT_INDEX ; 
 size_t SCU_ERR_CNT_TX_DONE_CREDIT_TIMEOUT_INDEX ; 
 int /*<<< orphan*/  loss_of_sync_error_count ; 
 int /*<<< orphan*/  phy_reset_problem_count ; 
 int /*<<< orphan*/  received_dword_count ; 
 int /*<<< orphan*/  received_frame_after_done_count ; 
 int /*<<< orphan*/  received_frame_count ; 
 int /*<<< orphan*/  received_frame_crc_error_count ; 
 int /*<<< orphan*/  received_frame_without_credit_count ; 
 int /*<<< orphan*/  received_short_frame_count ; 
 int /*<<< orphan*/  running_disparity_error_count ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_1__*) ; 
 int /*<<< orphan*/  scu_link_layer_register_read (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transmit_dword_count ; 
 int /*<<< orphan*/  transmit_frame_count ; 

SCI_STATUS scic_phy_get_counter(
   SCI_PHY_HANDLE_T        phy,
   SCIC_PHY_COUNTER_ID_T   counter_id,
   U32                   * data
)
{
   SCIC_SDS_PHY_T *this_phy;
   SCI_STATUS status = SCI_SUCCESS;
   this_phy = (SCIC_SDS_PHY_T *)phy;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(this_phy),
      SCIC_LOG_OBJECT_PHY,
      "scic_phy_get_counter(0x%x, 0x%x) enter\n",
      this_phy, counter_id
   ));

   switch(counter_id)
   {
      case SCIC_PHY_COUNTER_RECEIVED_FRAME:
         *data = scu_link_layer_register_read(this_phy, received_frame_count);
         break;
      case SCIC_PHY_COUNTER_TRANSMITTED_FRAME:
         *data = scu_link_layer_register_read(this_phy, transmit_frame_count);
         break;
      case SCIC_PHY_COUNTER_RECEIVED_FRAME_DWORD:
         *data = scu_link_layer_register_read(this_phy, received_dword_count);
         break;
      case SCIC_PHY_COUNTER_TRANSMITTED_FRAME_DWORD:
         *data = scu_link_layer_register_read(this_phy, transmit_dword_count);
         break;
      case SCIC_PHY_COUNTER_LOSS_OF_SYNC_ERROR:
         *data = scu_link_layer_register_read(this_phy, loss_of_sync_error_count);
         break;
      case SCIC_PHY_COUNTER_RECEIVED_DISPARITY_ERROR:
         *data = scu_link_layer_register_read(this_phy, running_disparity_error_count);
         break;
      case SCIC_PHY_COUNTER_RECEIVED_FRAME_CRC_ERROR:
         *data = scu_link_layer_register_read(this_phy, received_frame_crc_error_count);
         break;
      case SCIC_PHY_COUNTER_RECEIVED_DONE_ACK_NAK_TIMEOUT:
         *data = this_phy->error_counter[SCU_ERR_CNT_RX_DONE_ACK_NAK_TIMEOUT_INDEX];
         break;
      case SCIC_PHY_COUNTER_TRANSMITTED_DONE_ACK_NAK_TIMEOUT:
         *data = this_phy->error_counter[SCU_ERR_CNT_TX_DONE_ACK_NAK_TIMEOUT_INDEX];
         break;
      case SCIC_PHY_COUNTER_INACTIVITY_TIMER_EXPIRED:
         *data = this_phy->error_counter[SCU_ERR_CNT_INACTIVITY_TIMER_EXPIRED_INDEX];
         break;
      case SCIC_PHY_COUNTER_RECEIVED_DONE_CREDIT_TIMEOUT:
         *data = this_phy->error_counter[SCU_ERR_CNT_RX_DONE_CREDIT_TIMEOUT_INDEX];
         break;
      case SCIC_PHY_COUNTER_TRANSMITTED_DONE_CREDIT_TIMEOUT:
         *data = this_phy->error_counter[SCU_ERR_CNT_TX_DONE_CREDIT_TIMEOUT_INDEX];
         break;
      case SCIC_PHY_COUNTER_RECEIVED_CREDIT_BLOCKED:
         *data = this_phy->error_counter[SCU_ERR_CNT_RX_CREDIT_BLOCKED_RECEIVED_INDEX];
         break;
      case SCIC_PHY_COUNTER_RECEIVED_SHORT_FRAME:
         *data = scu_link_layer_register_read(this_phy, received_short_frame_count);
         break;
      case SCIC_PHY_COUNTER_RECEIVED_FRAME_WITHOUT_CREDIT:
         *data = scu_link_layer_register_read(this_phy, received_frame_without_credit_count);
         break;
      case SCIC_PHY_COUNTER_RECEIVED_FRAME_AFTER_DONE:
         *data = scu_link_layer_register_read(this_phy, received_frame_after_done_count);
         break;
      case SCIC_PHY_COUNTER_SN_DWORD_SYNC_ERROR:
         *data = scu_link_layer_register_read(this_phy, phy_reset_problem_count);
         break;
      default:
         status = SCI_FAILURE;
         break;
   }

   return status;
}