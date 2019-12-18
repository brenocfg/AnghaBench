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
typedef  scalar_t__ U16 ;
struct TYPE_2__ {scalar_t__* io_request_sequence; int /*<<< orphan*/  tci_pool; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  scalar_t__ SCI_CONTROLLER_HANDLE_T ;
typedef  TYPE_1__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  SCIC_LOG_OBJECT_CONTROLLER ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ SCI_CONTROLLER_INVALID_IO_TAG ; 
 int /*<<< orphan*/  SCI_FAILURE_INVALID_IO_TAG ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_object_get_logger (scalar_t__) ; 
 int /*<<< orphan*/  sci_pool_full (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_pool_put (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  scic_sds_io_sequence_increment (scalar_t__) ; 
 scalar_t__ scic_sds_io_tag_get_index (scalar_t__) ; 
 scalar_t__ scic_sds_io_tag_get_sequence (scalar_t__) ; 

SCI_STATUS scic_controller_free_io_tag(
   SCI_CONTROLLER_HANDLE_T controller,
   U16                     io_tag
)
{
   U16 sequence;
   U16 index;

   SCIC_SDS_CONTROLLER_T *this_controller;
   this_controller = (SCIC_SDS_CONTROLLER_T *)controller;

   ASSERT(io_tag != SCI_CONTROLLER_INVALID_IO_TAG);

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(controller),
      SCIC_LOG_OBJECT_CONTROLLER,
      "scic_controller_free_io_tag(0x%x, 0x%x) enter\n",
      controller, io_tag
   ));

   sequence = scic_sds_io_tag_get_sequence(io_tag);
   index    = scic_sds_io_tag_get_index(io_tag);

   if (!sci_pool_full(this_controller->tci_pool))
   {
      if (sequence == this_controller->io_request_sequence[index])
      {
         scic_sds_io_sequence_increment(
            this_controller->io_request_sequence[index]);

         sci_pool_put(this_controller->tci_pool, index);

         return SCI_SUCCESS;
      }
   }

   return SCI_FAILURE_INVALID_IO_TAG;
}