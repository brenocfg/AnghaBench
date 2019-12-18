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
typedef  size_t U16 ;
struct TYPE_2__ {size_t* io_request_sequence; int /*<<< orphan*/  tci_pool; } ;
typedef  scalar_t__ SCI_CONTROLLER_HANDLE_T ;
typedef  TYPE_1__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_OBJECT_CONTROLLER ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 size_t SCI_CONTROLLER_INVALID_IO_TAG ; 
 int /*<<< orphan*/  sci_base_object_get_logger (scalar_t__) ; 
 int /*<<< orphan*/  sci_pool_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_pool_get (int /*<<< orphan*/ ,size_t) ; 
 size_t scic_sds_io_tag_construct (size_t,size_t) ; 

U16 scic_controller_allocate_io_tag(
   SCI_CONTROLLER_HANDLE_T controller
)
{
   U16 task_context;
   U16 sequence_count;
   SCIC_SDS_CONTROLLER_T *this_controller;
   this_controller = (SCIC_SDS_CONTROLLER_T *)controller;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(controller),
      SCIC_LOG_OBJECT_CONTROLLER,
      "scic_controller_allocate_io_tag(0x%x) enter\n",
      controller
   ));

   if (!sci_pool_empty(this_controller->tci_pool))
   {
      sci_pool_get(this_controller->tci_pool, task_context);

      sequence_count = this_controller->io_request_sequence[task_context];

      return scic_sds_io_tag_construct(sequence_count, task_context);
   }

   return SCI_CONTROLLER_INVALID_IO_TAG;
}