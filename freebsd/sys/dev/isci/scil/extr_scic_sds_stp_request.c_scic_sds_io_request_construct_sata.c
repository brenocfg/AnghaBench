#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int U8 ;
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_13__ {int /*<<< orphan*/  state_machine; int /*<<< orphan*/  parent; } ;
struct TYPE_14__ {int sat_protocol; TYPE_1__ parent; int /*<<< orphan*/  started_substate_machine; int /*<<< orphan*/  protocol; } ;
typedef  scalar_t__ SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_IO_REQUEST_DATA_DIRECTION ;
typedef  TYPE_2__ SCIC_SDS_REQUEST_T ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  SAT_PROTOCOL_ATA_HARD_RESET 145 
#define  SAT_PROTOCOL_DEVICE_DIAGNOSTIC 144 
#define  SAT_PROTOCOL_DEVICE_RESET 143 
#define  SAT_PROTOCOL_DMA 142 
#define  SAT_PROTOCOL_DMA_QUEUED 141 
#define  SAT_PROTOCOL_FPDMA 140 
#define  SAT_PROTOCOL_NON_DATA 139 
#define  SAT_PROTOCOL_PACKET_DMA_DATA_IN 138 
#define  SAT_PROTOCOL_PACKET_DMA_DATA_OUT 137 
#define  SAT_PROTOCOL_PACKET_NON_DATA 136 
#define  SAT_PROTOCOL_PACKET_PIO_DATA_IN 135 
#define  SAT_PROTOCOL_PACKET_PIO_DATA_OUT 134 
#define  SAT_PROTOCOL_PIO_DATA_IN 133 
#define  SAT_PROTOCOL_PIO_DATA_OUT 132 
#define  SAT_PROTOCOL_RETURN_RESPONSE_INFO 131 
#define  SAT_PROTOCOL_SOFT_RESET 130 
#define  SAT_PROTOCOL_UDMA_DATA_IN 129 
#define  SAT_PROTOCOL_UDMA_DATA_OUT 128 
 int /*<<< orphan*/  SCIC_LOG_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_LOG_OBJECT_STP_IO_REQUEST ; 
 int /*<<< orphan*/  SCIC_SDS_STP_REQUEST_STARTED_UDMA_AWAIT_TC_COMPLETION_SUBSTATE ; 
 int /*<<< orphan*/  SCIC_STP_PROTOCOL ; 
 int /*<<< orphan*/  SCI_BASE_REQUEST_STATE_CONSTRUCTED ; 
 scalar_t__ SCI_FAILURE ; 
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  SCU_TASK_TYPE_DMA_IN ; 
 int /*<<< orphan*/  SCU_TASK_TYPE_FPDMAQ_READ ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_2__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_state_machine_construct (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_request_build_sgl (TYPE_2__*) ; 
 int /*<<< orphan*/  scic_sds_request_initialize_state_logging (TYPE_2__*) ; 
 scalar_t__ scic_sds_stp_non_data_request_construct (TYPE_2__*) ; 
 int /*<<< orphan*/  scic_sds_stp_non_ncq_request_construct (TYPE_2__*) ; 
 int /*<<< orphan*/  scic_sds_stp_optimized_request_construct (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ scic_sds_stp_packet_request_construct (TYPE_2__*) ; 
 scalar_t__ scic_sds_stp_pio_request_construct (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_stp_request_started_udma_substate_table ; 
 scalar_t__ scic_sds_stp_soft_reset_request_construct (TYPE_2__*) ; 

SCI_STATUS scic_sds_io_request_construct_sata(
   SCIC_SDS_REQUEST_T          * this_request,
   U8                            sat_protocol,
   U32                           transfer_length,
   SCI_IO_REQUEST_DATA_DIRECTION data_direction,
   BOOL                          copy_rx_frame,
   BOOL                          do_translate_sgl
)
{
   SCI_STATUS  status = SCI_SUCCESS;

   this_request->protocol = SCIC_STP_PROTOCOL;

   this_request->sat_protocol = sat_protocol;

   switch (sat_protocol)
   {
   case SAT_PROTOCOL_FPDMA:
      scic_sds_stp_optimized_request_construct(
         this_request,
         SCU_TASK_TYPE_FPDMAQ_READ,
         transfer_length,
         data_direction
      );

      // Copy over the SGL elements
      if (do_translate_sgl == TRUE)
         scic_sds_request_build_sgl(this_request);
   break;

   case SAT_PROTOCOL_UDMA_DATA_IN:
   case SAT_PROTOCOL_UDMA_DATA_OUT:
      scic_sds_stp_non_ncq_request_construct(this_request);

      scic_sds_stp_optimized_request_construct(
         this_request, SCU_TASK_TYPE_DMA_IN, transfer_length, data_direction
      );

      // Copy over the SGL elements
      if (do_translate_sgl == TRUE)
         scic_sds_request_build_sgl(this_request);

      sci_base_state_machine_construct(
         &this_request->started_substate_machine,
         &this_request->parent.parent,
         scic_sds_stp_request_started_udma_substate_table,
         SCIC_SDS_STP_REQUEST_STARTED_UDMA_AWAIT_TC_COMPLETION_SUBSTATE
      );
   break;

   case SAT_PROTOCOL_PIO_DATA_IN:
   case SAT_PROTOCOL_PIO_DATA_OUT:
      status = scic_sds_stp_pio_request_construct(
                  this_request, sat_protocol, copy_rx_frame);
   break;

   case SAT_PROTOCOL_ATA_HARD_RESET:
   case SAT_PROTOCOL_SOFT_RESET:
      status = scic_sds_stp_soft_reset_request_construct(this_request);
   break;

   case SAT_PROTOCOL_NON_DATA:
      status = scic_sds_stp_non_data_request_construct(this_request);
   break;

#if !defined(DISABLE_ATAPI)
   case SAT_PROTOCOL_PACKET_NON_DATA:
   case SAT_PROTOCOL_PACKET_DMA_DATA_IN:
   case SAT_PROTOCOL_PACKET_DMA_DATA_OUT:
   case SAT_PROTOCOL_PACKET_PIO_DATA_IN:
   case SAT_PROTOCOL_PACKET_PIO_DATA_OUT:
      status = scic_sds_stp_packet_request_construct(this_request);
      if (do_translate_sgl == TRUE)
         scic_sds_request_build_sgl(this_request);
   break;
#endif

   case SAT_PROTOCOL_DMA_QUEUED:
   case SAT_PROTOCOL_DMA:
   case SAT_PROTOCOL_DEVICE_DIAGNOSTIC:
   case SAT_PROTOCOL_DEVICE_RESET:
   case SAT_PROTOCOL_RETURN_RESPONSE_INFO:
   default:
      SCIC_LOG_ERROR((
         sci_base_object_get_logger(this_request),
         SCIC_LOG_OBJECT_STP_IO_REQUEST,
         "SCIC IO Request 0x%x received un-handled SAT Protocol %d.\n",
         this_request, sat_protocol
      ));

      status = SCI_FAILURE;
   break;
   }

   if (status == SCI_SUCCESS)
   {
      scic_sds_request_initialize_state_logging(this_request);

      sci_base_state_machine_change_state(
         &this_request->parent.state_machine,
         SCI_BASE_REQUEST_STATE_CONSTRUCTED
      );
   }

   return status;
}